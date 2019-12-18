#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nsinfo {scalar_t__ need_setns; } ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  F_OK ; 
 size_t PATH_MAX ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ asprintf (char**,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ build_id_cache__add_sdt_cache (char const*,char*,struct nsinfo*) ; 
 int /*<<< orphan*/  build_id_cache__basename (int,int,int) ; 
 char* build_id_cache__cachedir (char const*,char const*,struct nsinfo*,int,int) ; 
 char* build_id_cache__find_debug (char const*,struct nsinfo*) ; 
 int /*<<< orphan*/  build_id_cache__linkname (char const*,char*,size_t const) ; 
 char const* buildid_dir ; 
 scalar_t__ copyfile (char const*,char*) ; 
 scalar_t__ copyfile_ns (char const*,char*,struct nsinfo*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_regular_file (char*) ; 
 scalar_t__ link (char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ mkdir_p (char*,int) ; 
 char* nsinfo__realpath (char const*,struct nsinfo*) ; 
 int /*<<< orphan*/  pr_debug4 (char*,char*) ; 
 char* realpath (char const*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ symlink (char*,char*) ; 
 scalar_t__ unlink (char*) ; 
 char* zalloc (size_t const) ; 
 int /*<<< orphan*/  zfree (char**) ; 

int build_id_cache__add_s(const char *sbuild_id, const char *name,
			  struct nsinfo *nsi, bool is_kallsyms, bool is_vdso)
{
	const size_t size = PATH_MAX;
	char *realname = NULL, *filename = NULL, *dir_name = NULL,
	     *linkname = zalloc(size), *tmp;
	char *debugfile = NULL;
	int err = -1;

	if (!is_kallsyms) {
		if (!is_vdso)
			realname = nsinfo__realpath(name, nsi);
		else
			realname = realpath(name, NULL);
		if (!realname)
			goto out_free;
	}

	dir_name = build_id_cache__cachedir(sbuild_id, name, nsi, is_kallsyms,
					    is_vdso);
	if (!dir_name)
		goto out_free;

	/* Remove old style build-id cache */
	if (is_regular_file(dir_name))
		if (unlink(dir_name))
			goto out_free;

	if (mkdir_p(dir_name, 0755))
		goto out_free;

	/* Save the allocated buildid dirname */
	if (asprintf(&filename, "%s/%s", dir_name,
		     build_id_cache__basename(is_kallsyms, is_vdso,
		     false)) < 0) {
		filename = NULL;
		goto out_free;
	}

	if (access(filename, F_OK)) {
		if (is_kallsyms) {
			if (copyfile("/proc/kallsyms", filename))
				goto out_free;
		} else if (nsi && nsi->need_setns) {
			if (copyfile_ns(name, filename, nsi))
				goto out_free;
		} else if (link(realname, filename) && errno != EEXIST &&
				copyfile(name, filename))
			goto out_free;
	}

	/* Some binaries are stripped, but have .debug files with their symbol
	 * table.  Check to see if we can locate one of those, since the elf
	 * file itself may not be very useful to users of our tools without a
	 * symtab.
	 */
	if (!is_kallsyms && !is_vdso &&
	    strncmp(".ko", name + strlen(name) - 3, 3)) {
		debugfile = build_id_cache__find_debug(sbuild_id, nsi);
		if (debugfile) {
			zfree(&filename);
			if (asprintf(&filename, "%s/%s", dir_name,
			    build_id_cache__basename(false, false, true)) < 0) {
				filename = NULL;
				goto out_free;
			}
			if (access(filename, F_OK)) {
				if (nsi && nsi->need_setns) {
					if (copyfile_ns(debugfile, filename,
							nsi))
						goto out_free;
				} else if (link(debugfile, filename) &&
						errno != EEXIST &&
						copyfile(debugfile, filename))
					goto out_free;
			}
		}
	}

	if (!build_id_cache__linkname(sbuild_id, linkname, size))
		goto out_free;
	tmp = strrchr(linkname, '/');
	*tmp = '\0';

	if (access(linkname, X_OK) && mkdir_p(linkname, 0755))
		goto out_free;

	*tmp = '/';
	tmp = dir_name + strlen(buildid_dir) - 5;
	memcpy(tmp, "../..", 5);

	if (symlink(tmp, linkname) == 0)
		err = 0;

	/* Update SDT cache : error is just warned */
	if (realname &&
	    build_id_cache__add_sdt_cache(sbuild_id, realname, nsi) < 0)
		pr_debug4("Failed to update/scan SDT cache for %s\n", realname);

out_free:
	if (!is_kallsyms)
		free(realname);
	free(filename);
	free(debugfile);
	free(dir_name);
	free(linkname);
	return err;
}