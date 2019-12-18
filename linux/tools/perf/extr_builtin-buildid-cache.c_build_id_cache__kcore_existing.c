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
typedef  int /*<<< orphan*/  to_subdir ;
typedef  int /*<<< orphan*/  to ;
struct dirent {scalar_t__ d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compare_proc_modules (char*,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ same_kallsyms_reloc (char const*,char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int build_id_cache__kcore_existing(const char *from_dir, char *to_dir,
					  size_t to_dir_sz)
{
	char from[PATH_MAX];
	char to[PATH_MAX];
	char to_subdir[PATH_MAX];
	struct dirent *dent;
	int ret = -1;
	DIR *d;

	d = opendir(to_dir);
	if (!d)
		return -1;

	scnprintf(from, sizeof(from), "%s/modules", from_dir);

	while (1) {
		dent = readdir(d);
		if (!dent)
			break;
		if (dent->d_type != DT_DIR)
			continue;
		scnprintf(to, sizeof(to), "%s/%s/modules", to_dir,
			  dent->d_name);
		scnprintf(to_subdir, sizeof(to_subdir), "%s/%s",
			  to_dir, dent->d_name);
		if (!compare_proc_modules(from, to) &&
		    same_kallsyms_reloc(from_dir, to_subdir)) {
			strlcpy(to_dir, to_subdir, to_dir_sz);
			ret = 0;
			break;
		}
	}

	closedir(d);

	return ret;
}