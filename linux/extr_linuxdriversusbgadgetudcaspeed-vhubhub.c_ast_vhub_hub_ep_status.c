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
typedef  int u8 ;
typedef  int u16 ;
struct ast_vhub_ep {TYPE_1__* vhub; } ;
struct TYPE_2__ {scalar_t__ ep1_stalled; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPDBG (struct ast_vhub_ep*,char*,int) ; 
 int USB_ENDPOINT_HALT ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int ast_vhub_simple_reply (struct ast_vhub_ep*,int,int /*<<< orphan*/ ) ; 
 int std_req_stall ; 

__attribute__((used)) static int ast_vhub_hub_ep_status(struct ast_vhub_ep *ep,
				  u16 wIndex, u16 wValue)
{
	int ep_num;
	u8 st0 = 0;

	ep_num = wIndex & USB_ENDPOINT_NUMBER_MASK;
	EPDBG(ep, "GET_STATUS(ep%d)\n", ep_num);

	/* On the hub we have only EP 0 and 1 */
	if (ep_num == 1) {
		if (ep->vhub->ep1_stalled)
			st0 |= 1 << USB_ENDPOINT_HALT;
	} else if (ep_num != 0)
		return std_req_stall;

	return ast_vhub_simple_reply(ep, st0, 0);
}