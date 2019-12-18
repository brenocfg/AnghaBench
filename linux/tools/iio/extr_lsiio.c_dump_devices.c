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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ VERBLEVEL_SENSORS ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ check_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int closedir (int /*<<< orphan*/ *) ; 
 int dump_one_device (char*) ; 
 int dump_one_trigger (char*) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  iio_dir ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewinddir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  type_device ; 
 int /*<<< orphan*/  type_trigger ; 
 scalar_t__ verblevel ; 

__attribute__((used)) static int dump_devices(void)
{
	const struct dirent *ent;
	int ret;
	DIR *dp;

	dp = opendir(iio_dir);
	if (!dp) {
		fprintf(stderr, "No industrial I/O devices available\n");
		return -ENODEV;
	}

	while (ent = readdir(dp), ent) {
		if (check_prefix(ent->d_name, type_device)) {
			char *dev_dir_name;

			if (asprintf(&dev_dir_name, "%s%s", iio_dir,
				     ent->d_name) < 0) {
				ret = -ENOMEM;
				goto error_close_dir;
			}

			ret = dump_one_device(dev_dir_name);
			if (ret) {
				free(dev_dir_name);
				goto error_close_dir;
			}

			free(dev_dir_name);
			if (verblevel >= VERBLEVEL_SENSORS)
				printf("\n");
		}
	}
	rewinddir(dp);
	while (ent = readdir(dp), ent) {
		if (check_prefix(ent->d_name, type_trigger)) {
			char *dev_dir_name;

			if (asprintf(&dev_dir_name, "%s%s", iio_dir,
				     ent->d_name) < 0) {
				ret = -ENOMEM;
				goto error_close_dir;
			}

			ret = dump_one_trigger(dev_dir_name);
			if (ret) {
				free(dev_dir_name);
				goto error_close_dir;
			}

			free(dev_dir_name);
		}
	}

	return (closedir(dp) == -1) ? -errno : 0;

error_close_dir:
	if (closedir(dp) == -1)
		perror("dump_devices(): Failed to close directory");

	return ret;
}