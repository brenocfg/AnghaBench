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
struct TYPE_2__ {int /*<<< orphan*/  ctlstat; } ;
struct ast_vhub_ep {TYPE_1__ ep0; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPVDBG (struct ast_vhub_ep*,char*) ; 
 int /*<<< orphan*/  VHUB_EP0_RX_BUFF_RDY ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ast_vhub_ep0_rx_prime(struct ast_vhub_ep *ep)
{
	EPVDBG(ep, "rx prime\n");

	/* Prime endpoint for receiving data */
	writel(VHUB_EP0_RX_BUFF_RDY, ep->ep0.ctlstat);
}