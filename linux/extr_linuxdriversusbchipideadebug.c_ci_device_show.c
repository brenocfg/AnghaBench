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
struct usb_gadget {char* speed; char* max_speed; char* is_otg; char* is_a_peripheral; char* b_hnp_enable; char* a_hnp_support; char* a_alt_hnp_support; char* name; } ;
struct seq_file {struct ci_hdrc* private; } ;
struct ci_hdrc {TYPE_1__* driver; struct usb_gadget gadget; } ;
struct TYPE_2__ {char* function; char* max_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static int ci_device_show(struct seq_file *s, void *data)
{
	struct ci_hdrc *ci = s->private;
	struct usb_gadget *gadget = &ci->gadget;

	seq_printf(s, "speed             = %d\n", gadget->speed);
	seq_printf(s, "max_speed         = %d\n", gadget->max_speed);
	seq_printf(s, "is_otg            = %d\n", gadget->is_otg);
	seq_printf(s, "is_a_peripheral   = %d\n", gadget->is_a_peripheral);
	seq_printf(s, "b_hnp_enable      = %d\n", gadget->b_hnp_enable);
	seq_printf(s, "a_hnp_support     = %d\n", gadget->a_hnp_support);
	seq_printf(s, "a_alt_hnp_support = %d\n", gadget->a_alt_hnp_support);
	seq_printf(s, "name              = %s\n",
		   (gadget->name ? gadget->name : ""));

	if (!ci->driver)
		return 0;

	seq_printf(s, "gadget function   = %s\n",
		       (ci->driver->function ? ci->driver->function : ""));
	seq_printf(s, "gadget max speed  = %d\n", ci->driver->max_speed);

	return 0;
}