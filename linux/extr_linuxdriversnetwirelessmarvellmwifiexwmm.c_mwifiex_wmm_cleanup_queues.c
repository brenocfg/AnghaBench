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
struct TYPE_4__ {int /*<<< orphan*/  highest_queued_prio; int /*<<< orphan*/  tx_pkts_queued; TYPE_1__* tid_tbl_ptr; } ;
struct mwifiex_private {TYPE_2__ wmm; } ;
struct TYPE_3__ {int /*<<< orphan*/  ra_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIGH_PRIO_TID ; 
 int MAX_NUM_TID ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_wmm_del_pkts_in_ralist (struct mwifiex_private*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwifiex_wmm_cleanup_queues(struct mwifiex_private *priv)
{
	int i;

	for (i = 0; i < MAX_NUM_TID; i++)
		mwifiex_wmm_del_pkts_in_ralist(priv, &priv->wmm.tid_tbl_ptr[i].
								       ra_list);

	atomic_set(&priv->wmm.tx_pkts_queued, 0);
	atomic_set(&priv->wmm.highest_queued_prio, HIGH_PRIO_TID);
}