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
struct usb_function {int dummy; } ;
struct guas_setup_wq {unsigned int alt; int /*<<< orphan*/  work; struct f_uas* fu; } ;
struct f_uas {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int USB_GADGET_DELAYED_STATUS ; 
 unsigned int USB_G_ALT_INT_BBB ; 
 unsigned int USB_G_ALT_INT_UAS ; 
 struct guas_setup_wq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcm_delayed_set_alt ; 
 struct f_uas* to_f_uas (struct usb_function*) ; 

__attribute__((used)) static int tcm_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_uas *fu = to_f_uas(f);

	if ((alt == USB_G_ALT_INT_BBB) || (alt == USB_G_ALT_INT_UAS)) {
		struct guas_setup_wq *work;

		work = kmalloc(sizeof(*work), GFP_ATOMIC);
		if (!work)
			return -ENOMEM;
		INIT_WORK(&work->work, tcm_delayed_set_alt);
		work->fu = fu;
		work->alt = alt;
		schedule_work(&work->work);
		return USB_GADGET_DELAYED_STATUS;
	}
	return -EOPNOTSUPP;
}