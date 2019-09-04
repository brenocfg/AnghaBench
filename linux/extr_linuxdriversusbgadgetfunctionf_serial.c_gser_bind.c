#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct usb_function {int /*<<< orphan*/  name; } ;
struct usb_ep {int /*<<< orphan*/  name; } ;
struct usb_configuration {struct usb_composite_dev* cdev; } ;
struct usb_composite_dev {TYPE_2__* gadget; } ;
struct TYPE_14__ {struct usb_ep* out; struct usb_ep* in; } ;
struct f_gser {int data_id; TYPE_1__ port; int /*<<< orphan*/  port_num; } ;
struct TYPE_22__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_21__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_20__ {int bInterfaceNumber; } ;
struct TYPE_19__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_18__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_17__ {int id; } ;
struct TYPE_16__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ERROR (struct usb_composite_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct f_gser* func_to_gser (struct usb_function*) ; 
 scalar_t__ gadget_is_dualspeed (TYPE_2__*) ; 
 scalar_t__ gadget_is_superspeed (TYPE_2__*) ; 
 int /*<<< orphan*/  gser_fs_function ; 
 TYPE_3__ gser_fs_in_desc ; 
 TYPE_3__ gser_fs_out_desc ; 
 int /*<<< orphan*/  gser_hs_function ; 
 TYPE_9__ gser_hs_in_desc ; 
 TYPE_8__ gser_hs_out_desc ; 
 TYPE_7__ gser_interface_desc ; 
 int /*<<< orphan*/  gser_ss_function ; 
 TYPE_6__ gser_ss_in_desc ; 
 TYPE_5__ gser_ss_out_desc ; 
 TYPE_4__* gser_string_defs ; 
 int usb_assign_descriptors (struct usb_function*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_ep* usb_ep_autoconfig (TYPE_2__*,TYPE_3__*) ; 
 int usb_interface_id (struct usb_configuration*,struct usb_function*) ; 
 int usb_string_id (struct usb_composite_dev*) ; 

__attribute__((used)) static int gser_bind(struct usb_configuration *c, struct usb_function *f)
{
	struct usb_composite_dev *cdev = c->cdev;
	struct f_gser		*gser = func_to_gser(f);
	int			status;
	struct usb_ep		*ep;

	/* REVISIT might want instance-specific strings to help
	 * distinguish instances ...
	 */

	/* maybe allocate device-global string ID */
	if (gser_string_defs[0].id == 0) {
		status = usb_string_id(c->cdev);
		if (status < 0)
			return status;
		gser_string_defs[0].id = status;
	}

	/* allocate instance-specific interface IDs */
	status = usb_interface_id(c, f);
	if (status < 0)
		goto fail;
	gser->data_id = status;
	gser_interface_desc.bInterfaceNumber = status;

	status = -ENODEV;

	/* allocate instance-specific endpoints */
	ep = usb_ep_autoconfig(cdev->gadget, &gser_fs_in_desc);
	if (!ep)
		goto fail;
	gser->port.in = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &gser_fs_out_desc);
	if (!ep)
		goto fail;
	gser->port.out = ep;

	/* support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoints work at
	 * both speeds
	 */
	gser_hs_in_desc.bEndpointAddress = gser_fs_in_desc.bEndpointAddress;
	gser_hs_out_desc.bEndpointAddress = gser_fs_out_desc.bEndpointAddress;

	gser_ss_in_desc.bEndpointAddress = gser_fs_in_desc.bEndpointAddress;
	gser_ss_out_desc.bEndpointAddress = gser_fs_out_desc.bEndpointAddress;

	status = usb_assign_descriptors(f, gser_fs_function, gser_hs_function,
			gser_ss_function, NULL);
	if (status)
		goto fail;
	dev_dbg(&cdev->gadget->dev, "generic ttyGS%d: %s speed IN/%s OUT/%s\n",
		gser->port_num,
		gadget_is_superspeed(c->cdev->gadget) ? "super" :
		gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
		gser->port.in->name, gser->port.out->name);
	return 0;

fail:
	ERROR(cdev, "%s: can't bind, err %d\n", f->name, status);

	return status;
}