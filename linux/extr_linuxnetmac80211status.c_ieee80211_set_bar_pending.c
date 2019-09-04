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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct tid_ampdu_tx {int bar_pending; int /*<<< orphan*/  failed_bar_ssn; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tid_tx; } ;
struct sta_info {TYPE_1__ ampdu_mlme; } ;

/* Variables and functions */
 struct tid_ampdu_tx* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_set_bar_pending(struct sta_info *sta, u8 tid, u16 ssn)
{
	struct tid_ampdu_tx *tid_tx;

	tid_tx = rcu_dereference(sta->ampdu_mlme.tid_tx[tid]);
	if (!tid_tx)
		return;

	tid_tx->failed_bar_ssn = ssn;
	tid_tx->bar_pending = true;
}