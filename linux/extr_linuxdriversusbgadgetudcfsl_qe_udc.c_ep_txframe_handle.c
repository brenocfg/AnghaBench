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
struct qe_ep {int data01; int /*<<< orphan*/  txframe; TYPE_1__* udc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FRAME_ERROR ; 
 int PID_DATA0 ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  frame_create_tx (struct qe_ep*,int /*<<< orphan*/ ) ; 
 int frame_get_info (int /*<<< orphan*/ ) ; 
 int frame_get_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_ep_flushtxfifo (struct qe_ep*) ; 
 int /*<<< orphan*/  txcomplete (struct qe_ep*,int) ; 

__attribute__((used)) static int ep_txframe_handle(struct qe_ep *ep)
{
	if (frame_get_status(ep->txframe) & FRAME_ERROR) {
		qe_ep_flushtxfifo(ep);
		dev_vdbg(ep->udc->dev, "The EP0 transmit data have error!\n");
		if (frame_get_info(ep->txframe) & PID_DATA0)
			ep->data01 = 0;
		else
			ep->data01 = 1;

		txcomplete(ep, 1);
	} else
		txcomplete(ep, 0);

	frame_create_tx(ep, ep->txframe); /* send the data */
	return 0;
}