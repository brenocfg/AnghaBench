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
struct device {int dummy; } ;
struct usb_interface {struct device dev; } ;
struct i2400m {scalar_t__ updown; } ;
struct i2400mu {struct i2400m i2400m; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct usb_interface*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct usb_interface*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*) ; 
 int /*<<< orphan*/  i2400mu_notification_setup (struct i2400mu*) ; 
 int /*<<< orphan*/  rmb () ; 
 struct i2400mu* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static
int i2400mu_resume(struct usb_interface *iface)
{
	int ret = 0;
	struct device *dev = &iface->dev;
	struct i2400mu *i2400mu = usb_get_intfdata(iface);
	struct i2400m *i2400m = &i2400mu->i2400m;

	d_fnstart(3, dev, "(iface %p)\n", iface);
	rmb();		/* see i2400m->updown's documentation  */
	if (i2400m->updown == 0) {
		d_printf(1, dev, "fw was down, no resume needed\n");
		goto out;
	}
	d_printf(1, dev, "fw was up, resuming\n");
	i2400mu_notification_setup(i2400mu);
	/* USB has flow control, so we don't need to give it time to
	 * come back; otherwise, we'd use something like a get-state
	 * command... */
out:
	d_fnend(3, dev, "(iface %p) = %d\n", iface, ret);
	return ret;
}