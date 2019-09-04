#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ **** dirent ;
typedef  int /*<<< orphan*/  cdev_name ;
struct TYPE_4__ {int max_cdev_instance; TYPE_1__* cdi; int /*<<< orphan*/  nr_cooling_dev; } ;
struct TYPE_3__ {int instance; int /*<<< orphan*/  flag; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 char* CDEV ; 
 int /*<<< orphan*/  CDEV_FLAG_IN_CONTROL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 char* THERMAL_SYSFS ; 
 int /*<<< orphan*/  alphasort ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_cdev ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ******) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 TYPE_2__ ptdata ; 
 int scandir (char*,int /*<<< orphan*/ *******,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_get_string (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int scan_cdevs(void)
{
	DIR *dir;
	struct dirent **namelist;
	char cdev_name[256];
	int i, n, k = 0;

	if (!ptdata.nr_cooling_dev) {
		fprintf(stderr, "No cooling devices found\n");
		return 0;
	}
	for (i = 0; i <= ptdata.max_cdev_instance; i++) {
		memset(cdev_name, 0, sizeof(cdev_name));
		snprintf(cdev_name, 256, "%s/%s%d", THERMAL_SYSFS, CDEV, i);

		dir = opendir(cdev_name);
		if (!dir) {
			syslog(LOG_INFO, "Cooling dev %s skipped\n", cdev_name);
			/* there is a gap in cooling device id, check again
			 * for the same index.
			 */
			continue;
		}

		n = scandir(cdev_name, &namelist, 0, alphasort);
		if (n < 0)
			syslog(LOG_ERR, "scandir failed in %s",  cdev_name);
		else {
			sysfs_get_string(cdev_name, "type", ptdata.cdi[k].type);
			ptdata.cdi[k].instance = i;
			if (strstr(ptdata.cdi[k].type, ctrl_cdev)) {
				ptdata.cdi[k].flag |= CDEV_FLAG_IN_CONTROL;
				syslog(LOG_DEBUG, "control cdev id %d\n", i);
			}
			while (n--)
				free(namelist[n]);
			free(namelist);
		}
		closedir(dir);
		k++;
	}
	return 0;
}