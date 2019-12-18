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
typedef  void* uint32_t ;
struct gpiohandle_data {unsigned int lineoffset; int fd; int* values; int /*<<< orphan*/  consumer_label; void* eventflags; void* handleflags; } ;
struct gpioevent_request {unsigned int lineoffset; int fd; int* values; int /*<<< orphan*/  consumer_label; void* eventflags; void* handleflags; } ;
struct gpioevent_data {int id; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENOMEM ; 
#define  GPIOEVENT_EVENT_FALLING_EDGE 129 
#define  GPIOEVENT_EVENT_RISING_EDGE 128 
 int /*<<< orphan*/  GPIOHANDLE_GET_LINE_VALUES_IOCTL ; 
 int /*<<< orphan*/  GPIO_GET_LINEEVENT_IOCTL ; 
 int asprintf (char**,char*,char const*) ; 
 int close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct gpiohandle_data*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,struct gpioevent_data*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int monitor_device(const char *device_name,
		   unsigned int line,
		   uint32_t handleflags,
		   uint32_t eventflags,
		   unsigned int loops)
{
	struct gpioevent_request req;
	struct gpiohandle_data data;
	char *chrdev_name;
	int fd;
	int ret;
	int i = 0;

	ret = asprintf(&chrdev_name, "/dev/%s", device_name);
	if (ret < 0)
		return -ENOMEM;

	fd = open(chrdev_name, 0);
	if (fd == -1) {
		ret = -errno;
		fprintf(stderr, "Failed to open %s\n", chrdev_name);
		goto exit_close_error;
	}

	req.lineoffset = line;
	req.handleflags = handleflags;
	req.eventflags = eventflags;
	strcpy(req.consumer_label, "gpio-event-mon");

	ret = ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &req);
	if (ret == -1) {
		ret = -errno;
		fprintf(stderr, "Failed to issue GET EVENT "
			"IOCTL (%d)\n",
			ret);
		goto exit_close_error;
	}

	/* Read initial states */
	ret = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
	if (ret == -1) {
		ret = -errno;
		fprintf(stderr, "Failed to issue GPIOHANDLE GET LINE "
			"VALUES IOCTL (%d)\n",
			ret);
		goto exit_close_error;
	}

	fprintf(stdout, "Monitoring line %d on %s\n", line, device_name);
	fprintf(stdout, "Initial line value: %d\n", data.values[0]);

	while (1) {
		struct gpioevent_data event;

		ret = read(req.fd, &event, sizeof(event));
		if (ret == -1) {
			if (errno == -EAGAIN) {
				fprintf(stderr, "nothing available\n");
				continue;
			} else {
				ret = -errno;
				fprintf(stderr, "Failed to read event (%d)\n",
					ret);
				break;
			}
		}

		if (ret != sizeof(event)) {
			fprintf(stderr, "Reading event failed\n");
			ret = -EIO;
			break;
		}
		fprintf(stdout, "GPIO EVENT %llu: ", event.timestamp);
		switch (event.id) {
		case GPIOEVENT_EVENT_RISING_EDGE:
			fprintf(stdout, "rising edge");
			break;
		case GPIOEVENT_EVENT_FALLING_EDGE:
			fprintf(stdout, "falling edge");
			break;
		default:
			fprintf(stdout, "unknown event");
		}
		fprintf(stdout, "\n");

		i++;
		if (i == loops)
			break;
	}

exit_close_error:
	if (close(fd) == -1)
		perror("Failed to close GPIO character device file");
	free(chrdev_name);
	return ret;
}