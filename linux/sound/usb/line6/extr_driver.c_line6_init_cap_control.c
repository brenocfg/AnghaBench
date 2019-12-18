#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_line6 {int /*<<< orphan*/  ifcdev; void* buffer_message; TYPE_1__* properties; int /*<<< orphan*/  urb_listen; void* buffer_listen; } ;
struct TYPE_2__ {int capabilities; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LINE6_BUFSIZE_LISTEN ; 
 int LINE6_CAP_CONTROL_MIDI ; 
 int /*<<< orphan*/  LINE6_MIDI_MESSAGE_MAXLEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int line6_hwdep_init (struct usb_line6*) ; 
 int line6_start_listen (struct usb_line6*) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int line6_init_cap_control(struct usb_line6 *line6)
{
	int ret;

	/* initialize USB buffers: */
	line6->buffer_listen = kmalloc(LINE6_BUFSIZE_LISTEN, GFP_KERNEL);
	if (!line6->buffer_listen)
		return -ENOMEM;

	line6->urb_listen = usb_alloc_urb(0, GFP_KERNEL);
	if (!line6->urb_listen)
		return -ENOMEM;

	if (line6->properties->capabilities & LINE6_CAP_CONTROL_MIDI) {
		line6->buffer_message = kmalloc(LINE6_MIDI_MESSAGE_MAXLEN, GFP_KERNEL);
		if (!line6->buffer_message)
			return -ENOMEM;
	} else {
		ret = line6_hwdep_init(line6);
		if (ret < 0)
			return ret;
	}

	ret = line6_start_listen(line6);
	if (ret < 0) {
		dev_err(line6->ifcdev, "cannot start listening: %d\n", ret);
		return ret;
	}

	return 0;
}