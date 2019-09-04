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
struct usb_gadget {int dummy; } ;
struct fsg_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*) ; 
 int /*<<< orphan*/  FSG_STATE_DISCONNECT ; 
 struct fsg_dev* get_gadget_data (struct usb_gadget*) ; 
 int /*<<< orphan*/  raise_exception (struct fsg_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsg_disconnect(struct usb_gadget *gadget)
{
	struct fsg_dev		*fsg = get_gadget_data(gadget);

	DBG(fsg, "disconnect or port reset\n");
	raise_exception(fsg, FSG_STATE_DISCONNECT);
}