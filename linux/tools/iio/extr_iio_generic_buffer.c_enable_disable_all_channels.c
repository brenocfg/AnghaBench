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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  scanelemdir ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 char* FORMAT_SCAN_ELEMENTS_DIR ; 
 int closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ iioutils_check_suffix (char*,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int write_sysfs_int (char*,char*,int) ; 

__attribute__((used)) static int enable_disable_all_channels(char *dev_dir_name, int enable)
{
	const struct dirent *ent;
	char scanelemdir[256];
	DIR *dp;
	int ret;

	snprintf(scanelemdir, sizeof(scanelemdir),
		 FORMAT_SCAN_ELEMENTS_DIR, dev_dir_name);
	scanelemdir[sizeof(scanelemdir)-1] = '\0';

	dp = opendir(scanelemdir);
	if (!dp) {
		fprintf(stderr, "Enabling/disabling channels: can't open %s\n",
			scanelemdir);
		return -EIO;
	}

	ret = -ENOENT;
	while (ent = readdir(dp), ent) {
		if (iioutils_check_suffix(ent->d_name, "_en")) {
			printf("%sabling: %s\n",
			       enable ? "En" : "Dis",
			       ent->d_name);
			ret = write_sysfs_int(ent->d_name, scanelemdir,
					      enable);
			if (ret < 0)
				fprintf(stderr, "Failed to enable/disable %s\n",
					ent->d_name);
		}
	}

	if (closedir(dp) == -1) {
		perror("Enabling/disabling channels: "
		       "Failed to close directory");
		return -errno;
	}
	return 0;
}