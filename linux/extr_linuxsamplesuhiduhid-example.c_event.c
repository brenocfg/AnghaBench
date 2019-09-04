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
struct uhid_event {int type; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int EFAULT ; 
#define  UHID_CLOSE 133 
#define  UHID_OPEN 132 
#define  UHID_OUTPUT 131 
#define  UHID_OUTPUT_EV 130 
#define  UHID_START 129 
#define  UHID_STOP 128 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  handle_output (struct uhid_event*) ; 
 int /*<<< orphan*/  memset (struct uhid_event*,int /*<<< orphan*/ ,int) ; 
 int read (int,struct uhid_event*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int event(int fd)
{
	struct uhid_event ev;
	ssize_t ret;

	memset(&ev, 0, sizeof(ev));
	ret = read(fd, &ev, sizeof(ev));
	if (ret == 0) {
		fprintf(stderr, "Read HUP on uhid-cdev\n");
		return -EFAULT;
	} else if (ret < 0) {
		fprintf(stderr, "Cannot read uhid-cdev: %m\n");
		return -errno;
	} else if (ret != sizeof(ev)) {
		fprintf(stderr, "Invalid size read from uhid-dev: %ld != %lu\n",
			ret, sizeof(ev));
		return -EFAULT;
	}

	switch (ev.type) {
	case UHID_START:
		fprintf(stderr, "UHID_START from uhid-dev\n");
		break;
	case UHID_STOP:
		fprintf(stderr, "UHID_STOP from uhid-dev\n");
		break;
	case UHID_OPEN:
		fprintf(stderr, "UHID_OPEN from uhid-dev\n");
		break;
	case UHID_CLOSE:
		fprintf(stderr, "UHID_CLOSE from uhid-dev\n");
		break;
	case UHID_OUTPUT:
		fprintf(stderr, "UHID_OUTPUT from uhid-dev\n");
		handle_output(&ev);
		break;
	case UHID_OUTPUT_EV:
		fprintf(stderr, "UHID_OUTPUT_EV from uhid-dev\n");
		break;
	default:
		fprintf(stderr, "Invalid event from uhid-dev: %u\n", ev.type);
	}

	return 0;
}