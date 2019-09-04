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
typedef  size_t u8 ;
struct qe_udc {struct qe_ep* eps; } ;
struct qe_ep {int /*<<< orphan*/ * tx_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  nuke (struct qe_ep*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udc_reset_ep_queue(struct qe_udc *udc, u8 pipe)
{
	struct qe_ep *ep = &udc->eps[pipe];

	nuke(ep, -ECONNRESET);
	ep->tx_req = NULL;
	return 0;
}