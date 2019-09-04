#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct hfa384x_usbctlx {int state; TYPE_3__ outbuf; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  completing; } ;
struct hfa384x {TYPE_2__* wlandev; int /*<<< orphan*/  completion_bh; TYPE_1__ ctlxq; } ;
struct TYPE_5__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
#define  CTLX_COMPLETE 129 
#define  CTLX_REQ_FAILED 128 
 int /*<<< orphan*/  ctlxstr (int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlocked_usbctlx_complete(struct hfa384x *hw,
				      struct hfa384x_usbctlx *ctlx)
{
	/* Timers have been stopped, and ctlx should be in
	 * a terminal state. Retire it from the "active"
	 * queue.
	 */
	list_move_tail(&ctlx->list, &hw->ctlxq.completing);
	tasklet_schedule(&hw->completion_bh);

	switch (ctlx->state) {
	case CTLX_COMPLETE:
	case CTLX_REQ_FAILED:
		/* This are the correct terminating states. */
		break;

	default:
		netdev_err(hw->wlandev->netdev, "CTLX[%d] not in a terminating state(%s)\n",
			   le16_to_cpu(ctlx->outbuf.type),
			   ctlxstr(ctlx->state));
		break;
	}			/* switch */
}