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
struct dso {scalar_t__ symtab_type; char* long_name; scalar_t__ has_build_id; } ;
typedef  int /*<<< orphan*/  linkname ;

/* Variables and functions */
 scalar_t__ DSO_BINARY_TYPE__KALLSYMS ; 
 int /*<<< orphan*/  DSO__NAME_KALLSYMS ; 
 int ENOMEM ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  R_OK ; 
 int SBUILD_ID_SIZE ; 
 int SYMBOL_ANNOTATE_ERRNO__NO_VMLINUX ; 
 int /*<<< orphan*/  __symbol__join_symfs (char*,size_t,char*) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirname (char*) ; 
 char* dso__build_id_filename (struct dso*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dso__is_kcore (struct dso*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ readlink (char*,char*,int) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dso__disassemble_filename(struct dso *dso, char *filename, size_t filename_size)
{
	char linkname[PATH_MAX];
	char *build_id_filename;
	char *build_id_path = NULL;
	char *pos;

	if (dso->symtab_type == DSO_BINARY_TYPE__KALLSYMS &&
	    !dso__is_kcore(dso))
		return SYMBOL_ANNOTATE_ERRNO__NO_VMLINUX;

	build_id_filename = dso__build_id_filename(dso, NULL, 0, false);
	if (build_id_filename) {
		__symbol__join_symfs(filename, filename_size, build_id_filename);
		free(build_id_filename);
	} else {
		if (dso->has_build_id)
			return ENOMEM;
		goto fallback;
	}

	build_id_path = strdup(filename);
	if (!build_id_path)
		return ENOMEM;

	/*
	 * old style build-id cache has name of XX/XXXXXXX.. while
	 * new style has XX/XXXXXXX../{elf,kallsyms,vdso}.
	 * extract the build-id part of dirname in the new style only.
	 */
	pos = strrchr(build_id_path, '/');
	if (pos && strlen(pos) < SBUILD_ID_SIZE - 2)
		dirname(build_id_path);

	if (dso__is_kcore(dso) ||
	    readlink(build_id_path, linkname, sizeof(linkname)) < 0 ||
	    strstr(linkname, DSO__NAME_KALLSYMS) ||
	    access(filename, R_OK)) {
fallback:
		/*
		 * If we don't have build-ids or the build-id file isn't in the
		 * cache, or is just a kallsyms file, well, lets hope that this
		 * DSO is the same as when 'perf record' ran.
		 */
		__symbol__join_symfs(filename, filename_size, dso->long_name);
	}

	free(build_id_path);
	return 0;
}