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
struct tid_ampdu_tx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tid_tx; int /*<<< orphan*/  mtx; } ;
struct sta_info {TYPE_1__ ampdu_mlme; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tid_ampdu_tx*) ; 

void ieee80211_assign_tid_tx(struct sta_info *sta, int tid,
			     struct tid_ampdu_tx *tid_tx)
{
	lockdep_assert_held(&sta->ampdu_mlme.mtx);
	lockdep_assert_held(&sta->lock);
	rcu_assign_pointer(sta->ampdu_mlme.tid_tx[tid], tid_tx);
}