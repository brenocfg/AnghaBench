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
struct sk_buff {int dummy; } ;
struct ath10k_wmi {int /*<<< orphan*/  mgmt_max_num_pending_tx; int /*<<< orphan*/  mgmt_pending_tx; } ;
struct ath10k_mgmt_tx_pkt_addr {int /*<<< orphan*/  paddr; struct sk_buff* vaddr; } ;
struct ath10k {int /*<<< orphan*/  data_lock; struct ath10k_wmi wmi; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct ath10k_mgmt_tx_pkt_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath10k_mgmt_tx_pkt_addr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath10k_wmi_mgmt_tx_alloc_msdu_id(struct ath10k *ar, struct sk_buff *skb,
				 dma_addr_t paddr)
{
	struct ath10k_wmi *wmi = &ar->wmi;
	struct ath10k_mgmt_tx_pkt_addr *pkt_addr;
	int ret;

	pkt_addr = kmalloc(sizeof(*pkt_addr), GFP_ATOMIC);
	if (!pkt_addr)
		return -ENOMEM;

	pkt_addr->vaddr = skb;
	pkt_addr->paddr = paddr;

	spin_lock_bh(&ar->data_lock);
	ret = idr_alloc(&wmi->mgmt_pending_tx, pkt_addr, 0,
			wmi->mgmt_max_num_pending_tx, GFP_ATOMIC);
	spin_unlock_bh(&ar->data_lock);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi mgmt tx alloc msdu_id ret %d\n", ret);
	return ret;
}