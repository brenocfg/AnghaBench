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
typedef  int /*<<< orphan*/  to_dir ;
typedef  int /*<<< orphan*/  from_dir ;
typedef  int /*<<< orphan*/  dir ;

/* Variables and functions */
 int /*<<< orphan*/  DSO__NAME_KCORE ; 
 int PATH_MAX ; 
 int SBUILD_ID_SIZE ; 
 scalar_t__ build_id_cache__kcore_buildid (char*,char*) ; 
 scalar_t__ build_id_cache__kcore_dir (char*,int) ; 
 int /*<<< orphan*/  build_id_cache__kcore_existing (char*,char*,int) ; 
 int /*<<< orphan*/  buildid_dir ; 
 scalar_t__ kcore_copy (char*,char*) ; 
 scalar_t__ mkdir_p (char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int build_id_cache__add_kcore(const char *filename, bool force)
{
	char dir[32], sbuildid[SBUILD_ID_SIZE];
	char from_dir[PATH_MAX], to_dir[PATH_MAX];
	char *p;

	strlcpy(from_dir, filename, sizeof(from_dir));

	p = strrchr(from_dir, '/');
	if (!p || strcmp(p + 1, "kcore"))
		return -1;
	*p = '\0';

	if (build_id_cache__kcore_buildid(from_dir, sbuildid) < 0)
		return -1;

	scnprintf(to_dir, sizeof(to_dir), "%s/%s/%s",
		  buildid_dir, DSO__NAME_KCORE, sbuildid);

	if (!force &&
	    !build_id_cache__kcore_existing(from_dir, to_dir, sizeof(to_dir))) {
		pr_debug("same kcore found in %s\n", to_dir);
		return 0;
	}

	if (build_id_cache__kcore_dir(dir, sizeof(dir)))
		return -1;

	scnprintf(to_dir, sizeof(to_dir), "%s/%s/%s/%s",
		  buildid_dir, DSO__NAME_KCORE, sbuildid, dir);

	if (mkdir_p(to_dir, 0755))
		return -1;

	if (kcore_copy(from_dir, to_dir)) {
		/* Remove YYYYmmddHHMMSShh directory */
		if (!rmdir(to_dir)) {
			p = strrchr(to_dir, '/');
			if (p)
				*p = '\0';
			/* Try to remove buildid directory */
			if (!rmdir(to_dir)) {
				p = strrchr(to_dir, '/');
				if (p)
					*p = '\0';
				/* Try to remove [kernel.kcore] directory */
				rmdir(to_dir);
			}
		}
		return -1;
	}

	pr_debug("kcore added to build-id cache directory %s\n", to_dir);

	return 0;
}