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
struct gpioline_info {char* name; char* label; int lines; int line_offset; char* consumer; scalar_t__ flags; } ;
struct gpiochip_info {char* name; char* label; int lines; int line_offset; char* consumer; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  linfo ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GPIO_GET_CHIPINFO_IOCTL ; 
 int /*<<< orphan*/  GPIO_GET_LINEINFO_IOCTL ; 
 int asprintf (char**,char*,char const*) ; 
 int close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct gpioline_info*) ; 
 int /*<<< orphan*/  memset (struct gpioline_info*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_flags (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int list_device(const char *device_name)
{
	struct gpiochip_info cinfo;
	char *chrdev_name;
	int fd;
	int ret;
	int i;

	ret = asprintf(&chrdev_name, "/dev/%s", device_name);
	if (ret < 0)
		return -ENOMEM;

	fd = open(chrdev_name, 0);
	if (fd == -1) {
		ret = -errno;
		fprintf(stderr, "Failed to open %s\n", chrdev_name);
		goto exit_close_error;
	}

	/* Inspect this GPIO chip */
	ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &cinfo);
	if (ret == -1) {
		ret = -errno;
		perror("Failed to issue CHIPINFO IOCTL\n");
		goto exit_close_error;
	}
	fprintf(stdout, "GPIO chip: %s, \"%s\", %u GPIO lines\n",
		cinfo.name, cinfo.label, cinfo.lines);

	/* Loop over the lines and print info */
	for (i = 0; i < cinfo.lines; i++) {
		struct gpioline_info linfo;

		memset(&linfo, 0, sizeof(linfo));
		linfo.line_offset = i;

		ret = ioctl(fd, GPIO_GET_LINEINFO_IOCTL, &linfo);
		if (ret == -1) {
			ret = -errno;
			perror("Failed to issue LINEINFO IOCTL\n");
			goto exit_close_error;
		}
		fprintf(stdout, "\tline %2d:", linfo.line_offset);
		if (linfo.name[0])
			fprintf(stdout, " \"%s\"", linfo.name);
		else
			fprintf(stdout, " unnamed");
		if (linfo.consumer[0])
			fprintf(stdout, " \"%s\"", linfo.consumer);
		else
			fprintf(stdout, " unused");
		if (linfo.flags) {
			fprintf(stdout, " [");
			print_flags(linfo.flags);
			fprintf(stdout, "]");
		}
		fprintf(stdout, "\n");

	}

exit_close_error:
	if (close(fd) == -1)
		perror("Failed to close GPIO character device file");
	free(chrdev_name);
	return ret;
}