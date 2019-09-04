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
struct gpiochip_info {int /*<<< orphan*/  label; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ GC_NUM ; 
 int /*<<< orphan*/  GPIO_GET_CHIPINFO_IOCTL ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 struct gpiochip_info* calloc (int,scalar_t__) ; 
 scalar_t__ check_prefix (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (struct gpiochip_info*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct gpiochip_info*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 struct gpiochip_info* realloc (struct gpiochip_info*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static struct gpiochip_info *list_gpiochip(const char *gpiochip_name, int *ret)
{
	struct gpiochip_info *cinfo;
	struct gpiochip_info *current;
	const struct dirent *ent;
	DIR *dp;
	char *chrdev_name;
	int fd;
	int i = 0;

	cinfo = calloc(sizeof(struct gpiochip_info) * 4, GC_NUM + 1);
	if (!cinfo)
		err(EXIT_FAILURE, "gpiochip_info allocation failed");

	current = cinfo;
	dp = opendir("/dev");
	if (!dp) {
		*ret = -errno;
		goto error_out;
	} else {
		*ret = 0;
	}

	while (ent = readdir(dp), ent) {
		if (check_prefix(ent->d_name, "gpiochip")) {
			*ret = asprintf(&chrdev_name, "/dev/%s", ent->d_name);
			if (*ret < 0)
				goto error_out;

			fd = open(chrdev_name, 0);
			if (fd == -1) {
				*ret = -errno;
				fprintf(stderr, "Failed to open %s\n",
					chrdev_name);
				goto error_close_dir;
			}
			*ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, current);
			if (*ret == -1) {
				perror("Failed to issue CHIPINFO IOCTL\n");
				goto error_close_dir;
			}
			close(fd);
			if (strcmp(current->label, gpiochip_name) == 0
			    || check_prefix(current->label, gpiochip_name)) {
				*ret = 0;
				current++;
				i++;
			}
		}
	}

	if ((!*ret && i == 0) || *ret < 0) {
		free(cinfo);
		cinfo = NULL;
	}
	if (!*ret && i > 0) {
		cinfo = realloc(cinfo, sizeof(struct gpiochip_info) * 4 * i);
		*ret = i;
	}

error_close_dir:
	closedir(dp);
error_out:
	if (*ret < 0)
		err(EXIT_FAILURE, "list gpiochip failed: %s", strerror(*ret));

	return cinfo;
}