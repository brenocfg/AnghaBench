#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  buffer_unshare_reserve_bit; } ;
struct fjes_hw {int /*<<< orphan*/  epstop_task; int /*<<< orphan*/  epstop_req_bit; int /*<<< orphan*/  txrx_stop_req_bit; int /*<<< orphan*/  rx_status_lock; TYPE_5__* ep_shm_info; TYPE_1__ hw_info; } ;
struct fjes_adapter {int /*<<< orphan*/  control_wq; int /*<<< orphan*/  unshare_watch_task; int /*<<< orphan*/  unshare_watch_bitmask; struct fjes_hw hw; } ;
typedef  enum ep_partner_status { ____Placeholder_ep_partner_status } ep_partner_status ;
struct TYPE_9__ {TYPE_3__* info; } ;
struct TYPE_10__ {TYPE_4__ tx; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_status; } ;
struct TYPE_8__ {TYPE_2__ v1i; } ;

/* Variables and functions */
#define  EP_PARTNER_COMPLETE 131 
#define  EP_PARTNER_SHARED 130 
#define  EP_PARTNER_UNSHARE 129 
#define  EP_PARTNER_WAITING 128 
 int /*<<< orphan*/  FJES_RX_STOP_REQ_DONE ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int fjes_hw_get_partner_ep_status (struct fjes_hw*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_fjes_stop_req_irq_post (struct fjes_hw*,int) ; 
 int /*<<< orphan*/  trace_fjes_stop_req_irq_pre (struct fjes_hw*,int,int) ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fjes_stop_req_irq(struct fjes_adapter *adapter, int src_epid)
{
	struct fjes_hw *hw = &adapter->hw;
	enum ep_partner_status status;
	unsigned long flags;

	set_bit(src_epid, &hw->hw_info.buffer_unshare_reserve_bit);

	status = fjes_hw_get_partner_ep_status(hw, src_epid);
	trace_fjes_stop_req_irq_pre(hw, src_epid, status);
	switch (status) {
	case EP_PARTNER_WAITING:
		spin_lock_irqsave(&hw->rx_status_lock, flags);
		hw->ep_shm_info[src_epid].tx.info->v1i.rx_status |=
				FJES_RX_STOP_REQ_DONE;
		spin_unlock_irqrestore(&hw->rx_status_lock, flags);
		clear_bit(src_epid, &hw->txrx_stop_req_bit);
		/* fall through */
	case EP_PARTNER_UNSHARE:
	case EP_PARTNER_COMPLETE:
	default:
		set_bit(src_epid, &adapter->unshare_watch_bitmask);
		if (!work_pending(&adapter->unshare_watch_task))
			queue_work(adapter->control_wq,
				   &adapter->unshare_watch_task);
		break;
	case EP_PARTNER_SHARED:
		set_bit(src_epid, &hw->epstop_req_bit);

		if (!work_pending(&hw->epstop_task))
			queue_work(adapter->control_wq, &hw->epstop_task);
		break;
	}
	trace_fjes_stop_req_irq_post(hw, src_epid);
}