#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tx_ts_record {int /*<<< orphan*/  ts_add_ba_timer; } ;
struct ts_common_info {int /*<<< orphan*/  inact_timer; int /*<<< orphan*/  setup_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  prev; } ;
struct rx_ts_record {TYPE_2__ rx_pending_pkt_list; int /*<<< orphan*/  rx_pkt_pending_timer; } ;
struct ieee80211_rxb {int nr_subframes; int /*<<< orphan*/ * subframes; } ;
struct ieee80211_device {int /*<<< orphan*/  reorder_spinlock; int /*<<< orphan*/  RxReorder_Unused_List; } ;
typedef  enum tr_select { ____Placeholder_tr_select } tr_select ;
struct TYPE_3__ {int /*<<< orphan*/  List; struct ieee80211_rxb* prxb; } ;
typedef  TYPE_1__* PRX_REORDER_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  List ; 
 int RX_DIR ; 
 int /*<<< orphan*/  RX_REORDER_ENTRY ; 
 int /*<<< orphan*/  TsInitDelBA (struct ieee80211_device*,struct ts_common_info*,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_rxb*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_2__*) ; 
 scalar_t__ list_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void RemoveTsEntry(struct ieee80211_device *ieee, struct ts_common_info *pTs,
			  enum tr_select TxRxSelect)
{
	//u32 flags = 0;
	unsigned long flags = 0;
	del_timer_sync(&pTs->setup_timer);
	del_timer_sync(&pTs->inact_timer);
	TsInitDelBA(ieee, pTs, TxRxSelect);

	if(TxRxSelect == RX_DIR) {
//#ifdef TO_DO_LIST
		PRX_REORDER_ENTRY	pRxReorderEntry;
		struct rx_ts_record     *pRxTS = (struct rx_ts_record *)pTs;
		if(timer_pending(&pRxTS->rx_pkt_pending_timer))
			del_timer_sync(&pRxTS->rx_pkt_pending_timer);

		while(!list_empty(&pRxTS->rx_pending_pkt_list)) {
			spin_lock_irqsave(&(ieee->reorder_spinlock), flags);
			//pRxReorderEntry = list_entry(&pRxTS->rx_pending_pkt_list.prev,RX_REORDER_ENTRY,List);
			pRxReorderEntry = (PRX_REORDER_ENTRY)list_entry(pRxTS->rx_pending_pkt_list.prev,RX_REORDER_ENTRY,List);
			list_del_init(&pRxReorderEntry->List);
			{
				int i = 0;
				struct ieee80211_rxb *prxb = pRxReorderEntry->prxb;
				if (unlikely(!prxb)) {
					spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
					return;
				}
				for(i =0; i < prxb->nr_subframes; i++)
					dev_kfree_skb(prxb->subframes[i]);

				kfree(prxb);
				prxb = NULL;
			}
			list_add_tail(&pRxReorderEntry->List,&ieee->RxReorder_Unused_List);
			spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
		}

//#endif
	} else {
		struct tx_ts_record *pTxTS = (struct tx_ts_record *)pTs;
		del_timer_sync(&pTxTS->ts_add_ba_timer);
	}
}