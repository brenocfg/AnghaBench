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
typedef  scalar_t__ u32 ;
struct usb_line6 {int /*<<< orphan*/  startup_work; struct usb_device* usbdev; } ;
struct usb_line6_toneport {size_t source; struct usb_line6 line6; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int code; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TONEPORT_PCM_DELAY ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  line6_write_data (struct usb_line6*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ toneport_has_led (struct usb_line6_toneport*) ; 
 scalar_t__ toneport_has_source_select (struct usb_line6_toneport*) ; 
 int /*<<< orphan*/  toneport_send_cmd (struct usb_device*,int,int) ; 
 TYPE_1__* toneport_source_info ; 
 int /*<<< orphan*/  toneport_update_led (struct usb_line6_toneport*) ; 

__attribute__((used)) static int toneport_setup(struct usb_line6_toneport *toneport)
{
	u32 *ticks;
	struct usb_line6 *line6 = &toneport->line6;
	struct usb_device *usbdev = line6->usbdev;

	ticks = kmalloc(sizeof(*ticks), GFP_KERNEL);
	if (!ticks)
		return -ENOMEM;

	/* sync time on device with host: */
	/* note: 32-bit timestamps overflow in year 2106 */
	*ticks = (u32)ktime_get_real_seconds();
	line6_write_data(line6, 0x80c6, ticks, 4);
	kfree(ticks);

	/* enable device: */
	toneport_send_cmd(usbdev, 0x0301, 0x0000);

	/* initialize source select: */
	if (toneport_has_source_select(toneport))
		toneport_send_cmd(usbdev,
				  toneport_source_info[toneport->source].code,
				  0x0000);

	if (toneport_has_led(toneport))
		toneport_update_led(toneport);

	schedule_delayed_work(&toneport->line6.startup_work,
			      msecs_to_jiffies(TONEPORT_PCM_DELAY * 1000));
	return 0;
}