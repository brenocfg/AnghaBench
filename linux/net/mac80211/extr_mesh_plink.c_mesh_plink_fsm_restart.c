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
struct sta_info {TYPE_1__* mesh; } ;
struct TYPE_2__ {scalar_t__ plink_retries; scalar_t__ reason; scalar_t__ plid; scalar_t__ llid; int /*<<< orphan*/  plink_state; int /*<<< orphan*/  plink_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_PLINK_LISTEN ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mesh_plink_fsm_restart(struct sta_info *sta)
{
	lockdep_assert_held(&sta->mesh->plink_lock);
	sta->mesh->plink_state = NL80211_PLINK_LISTEN;
	sta->mesh->llid = sta->mesh->plid = sta->mesh->reason = 0;
	sta->mesh->plink_retries = 0;
}