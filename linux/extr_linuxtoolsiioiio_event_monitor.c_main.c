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
struct iio_event_data {int dummy; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IIO_GET_EVENT_FD_IOCTL ; 
 int asprintf (char**,char*,int) ; 
 int close (int) ; 
 int errno ; 
 int find_type_by_name (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_event (struct iio_event_data*) ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 
 int read (int,struct iio_event_data*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 

int main(int argc, char **argv)
{
	struct iio_event_data event;
	const char *device_name;
	char *chrdev_name;
	int ret;
	int dev_num;
	int fd, event_fd;

	if (argc <= 1) {
		fprintf(stderr, "Usage: %s <device_name>\n", argv[0]);
		return -1;
	}

	device_name = argv[1];

	dev_num = find_type_by_name(device_name, "iio:device");
	if (dev_num >= 0) {
		printf("Found IIO device with name %s with device number %d\n",
		       device_name, dev_num);
		ret = asprintf(&chrdev_name, "/dev/iio:device%d", dev_num);
		if (ret < 0)
			return -ENOMEM;
	} else {
		/*
		 * If we can't find an IIO device by name assume device_name is
		 * an IIO chrdev
		 */
		chrdev_name = strdup(device_name);
		if (!chrdev_name)
			return -ENOMEM;
	}

	fd = open(chrdev_name, 0);
	if (fd == -1) {
		ret = -errno;
		fprintf(stderr, "Failed to open %s\n", chrdev_name);
		goto error_free_chrdev_name;
	}

	ret = ioctl(fd, IIO_GET_EVENT_FD_IOCTL, &event_fd);
	if (ret == -1 || event_fd == -1) {
		ret = -errno;
		if (ret == -ENODEV)
			fprintf(stderr,
				"This device does not support events\n");
		else
			fprintf(stderr, "Failed to retrieve event fd\n");
		if (close(fd) == -1)
			perror("Failed to close character device file");

		goto error_free_chrdev_name;
	}

	if (close(fd) == -1)  {
		ret = -errno;
		goto error_free_chrdev_name;
	}

	while (true) {
		ret = read(event_fd, &event, sizeof(event));
		if (ret == -1) {
			if (errno == EAGAIN) {
				fprintf(stderr, "nothing available\n");
				continue;
			} else {
				ret = -errno;
				perror("Failed to read event from device");
				break;
			}
		}

		if (ret != sizeof(event)) {
			fprintf(stderr, "Reading event failed!\n");
			ret = -EIO;
			break;
		}

		print_event(&event);
	}

	if (close(event_fd) == -1)
		perror("Failed to close event file");

error_free_chrdev_name:
	free(chrdev_name);

	return ret;
}