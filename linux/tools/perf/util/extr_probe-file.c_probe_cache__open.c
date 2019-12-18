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
struct probe_cache {int fd; } ;
struct nsinfo {int dummy; } ;
struct nscookie {int dummy; } ;

/* Variables and functions */
 char* DSO__NAME_KALLSYMS ; 
 int ENOMEM ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int PATH_MAX ; 
 int SBUILD_ID_SIZE ; 
 int build_id_cache__add_s (char*,char const*,struct nsinfo*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ build_id_cache__cached (char const*) ; 
 char* build_id_cache__cachedir (char*,char const*,struct nsinfo*,int,int) ; 
 char* build_id_cache__linkname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int filename__sprintf_build_id (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  nsinfo__mountns_enter (struct nsinfo*,struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__mountns_exit (struct nscookie*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int sysfs__sprintf_build_id (char*,char*) ; 

__attribute__((used)) static int probe_cache__open(struct probe_cache *pcache, const char *target,
			     struct nsinfo *nsi)
{
	char cpath[PATH_MAX];
	char sbuildid[SBUILD_ID_SIZE];
	char *dir_name = NULL;
	bool is_kallsyms = false;
	int ret, fd;
	struct nscookie nsc;

	if (target && build_id_cache__cached(target)) {
		/* This is a cached buildid */
		strlcpy(sbuildid, target, SBUILD_ID_SIZE);
		dir_name = build_id_cache__linkname(sbuildid, NULL, 0);
		goto found;
	}

	if (!target || !strcmp(target, DSO__NAME_KALLSYMS)) {
		target = DSO__NAME_KALLSYMS;
		is_kallsyms = true;
		ret = sysfs__sprintf_build_id("/", sbuildid);
	} else {
		nsinfo__mountns_enter(nsi, &nsc);
		ret = filename__sprintf_build_id(target, sbuildid);
		nsinfo__mountns_exit(&nsc);
	}

	if (ret < 0) {
		pr_debug("Failed to get build-id from %s.\n", target);
		return ret;
	}

	/* If we have no buildid cache, make it */
	if (!build_id_cache__cached(sbuildid)) {
		ret = build_id_cache__add_s(sbuildid, target, nsi,
					    is_kallsyms, NULL);
		if (ret < 0) {
			pr_debug("Failed to add build-id cache: %s\n", target);
			return ret;
		}
	}

	dir_name = build_id_cache__cachedir(sbuildid, target, nsi, is_kallsyms,
					    false);
found:
	if (!dir_name) {
		pr_debug("Failed to get cache from %s\n", target);
		return -ENOMEM;
	}

	snprintf(cpath, PATH_MAX, "%s/probes", dir_name);
	fd = open(cpath, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		pr_debug("Failed to open cache(%d): %s\n", fd, cpath);
	free(dir_name);
	pcache->fd = fd;

	return fd;
}