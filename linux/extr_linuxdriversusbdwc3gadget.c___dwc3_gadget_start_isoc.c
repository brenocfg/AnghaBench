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
struct dwc3_ep {int /*<<< orphan*/  frame_number; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; TYPE_1__* dwc; int /*<<< orphan*/  pending_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_ALIGN_FRAME (struct dwc3_ep*) ; 
 int /*<<< orphan*/  DWC3_EP_PENDING_REQUEST ; 
 int /*<<< orphan*/  __dwc3_gadget_kick_transfer (struct dwc3_ep*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dwc3_gadget_start_isoc(struct dwc3_ep *dep)
{
	if (list_empty(&dep->pending_list)) {
		dev_info(dep->dwc->dev, "%s: ran out of requests\n",
				dep->name);
		dep->flags |= DWC3_EP_PENDING_REQUEST;
		return;
	}

	dep->frame_number = DWC3_ALIGN_FRAME(dep);
	__dwc3_gadget_kick_transfer(dep);
}