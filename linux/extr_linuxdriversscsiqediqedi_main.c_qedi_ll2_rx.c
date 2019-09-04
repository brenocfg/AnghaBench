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
typedef  int u32 ;
struct skb_work_list {int /*<<< orphan*/  list; scalar_t__ vlan_id; struct sk_buff* skb; } ;
struct sk_buff {int dummy; } ;
struct qedi_uio_dev {struct qedi_uio_ctrl* uctrl; } ;
struct qedi_uio_ctrl {int hw_rx_prod; int host_rx_cons; int /*<<< orphan*/  hw_rx_prod_cnt; } ;
struct qedi_ctx {int /*<<< orphan*/  ll2_lock; int /*<<< orphan*/  ll2_recv_thread; int /*<<< orphan*/  ll2_skb_list; int /*<<< orphan*/  dbg_ctx; struct qedi_uio_dev* udev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDI_LOG_UIO ; 
 int /*<<< orphan*/  QEDI_WARN (int /*<<< orphan*/ *,char*) ; 
 int RX_RING ; 
 int /*<<< orphan*/  UIO_DEV_OPENED ; 
 int /*<<< orphan*/  __vlan_insert_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct skb_work_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedi_ll2_rx(void *cookie, struct sk_buff *skb, u32 arg1, u32 arg2)
{
	struct qedi_ctx *qedi = (struct qedi_ctx *)cookie;
	struct qedi_uio_dev *udev;
	struct qedi_uio_ctrl *uctrl;
	struct skb_work_list *work;
	u32 prod;

	if (!qedi) {
		QEDI_ERR(NULL, "qedi is NULL\n");
		return -1;
	}

	if (!test_bit(UIO_DEV_OPENED, &qedi->flags)) {
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_UIO,
			  "UIO DEV is not opened\n");
		kfree_skb(skb);
		return 0;
	}

	udev = qedi->udev;
	uctrl = udev->uctrl;

	work = kzalloc(sizeof(*work), GFP_ATOMIC);
	if (!work) {
		QEDI_WARN(&qedi->dbg_ctx,
			  "Could not allocate work so dropping frame.\n");
		kfree_skb(skb);
		return 0;
	}

	INIT_LIST_HEAD(&work->list);
	work->skb = skb;

	if (skb_vlan_tag_present(skb))
		work->vlan_id = skb_vlan_tag_get(skb);

	if (work->vlan_id)
		__vlan_insert_tag(work->skb, htons(ETH_P_8021Q), work->vlan_id);

	spin_lock_bh(&qedi->ll2_lock);
	list_add_tail(&work->list, &qedi->ll2_skb_list);

	++uctrl->hw_rx_prod_cnt;
	prod = (uctrl->hw_rx_prod + 1) % RX_RING;
	if (prod != uctrl->host_rx_cons) {
		uctrl->hw_rx_prod = prod;
		spin_unlock_bh(&qedi->ll2_lock);
		wake_up_process(qedi->ll2_recv_thread);
		return 0;
	}

	spin_unlock_bh(&qedi->ll2_lock);
	return 0;
}