#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct wahc {TYPE_1__* usb_iface; } ;
struct TYPE_7__ {scalar_t__ hwa_bDeviceInfoIndex; scalar_t__ bSpeed; scalar_t__ bEndpointAddress; scalar_t__ bInterval; int bmAttribute; } ;
struct wa_rpipe {TYPE_3__ descr; } ;
struct TYPE_8__ {scalar_t__ bEndpointAddress; scalar_t__ bInterval; int bmAttributes; } ;
struct usb_host_endpoint {TYPE_4__ desc; } ;
struct urb {int /*<<< orphan*/  pipe; TYPE_2__* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {int /*<<< orphan*/  portnum; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UWB_PHY_RATE_200 ; 
 scalar_t__ UWB_PHY_RATE_53 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,int) ; 
 scalar_t__ usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ wusb_port_no_to_idx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpipe_check_aim(const struct wa_rpipe *rpipe, const struct wahc *wa,
			   const struct usb_host_endpoint *ep,
			   const struct urb *urb, gfp_t gfp)
{
	int result = 0;
	struct device *dev = &wa->usb_iface->dev;
	u8 portnum = wusb_port_no_to_idx(urb->dev->portnum);

#define AIM_CHECK(rdf, val, text)					\
	do {								\
		if (rpipe->descr.rdf != (val)) {			\
			dev_err(dev,					\
				"rpipe aim discrepancy: " #rdf " " text "\n", \
				rpipe->descr.rdf, (val));		\
			result = -EINVAL;				\
			WARN_ON(1);					\
		}							\
	} while (0)
	AIM_CHECK(hwa_bDeviceInfoIndex, portnum, "(%u vs %u)");
	AIM_CHECK(bSpeed, usb_pipeendpoint(urb->pipe) == 0 ?
			UWB_PHY_RATE_53 : UWB_PHY_RATE_200,
		  "(%u vs %u)");
	AIM_CHECK(bEndpointAddress, ep->desc.bEndpointAddress, "(%u vs %u)");
	AIM_CHECK(bInterval, ep->desc.bInterval, "(%u vs %u)");
	AIM_CHECK(bmAttribute, ep->desc.bmAttributes & 0x03, "(%u vs %u)");
#undef AIM_CHECK
	return result;
}