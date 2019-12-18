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
struct TYPE_2__ {int /*<<< orphan*/  proberesp_ies; int /*<<< orphan*/  hidden_beacon_bss; int /*<<< orphan*/  beacon_ies; } ;
struct cfg80211_internal_bss {int /*<<< orphan*/  hidden_list; TYPE_1__ pub; int /*<<< orphan*/  hold; } ;
struct cfg80211_bss_ies {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_internal_bss*) ; 
 int /*<<< orphan*/  kfree_rcu (struct cfg80211_bss_ies*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 

__attribute__((used)) static void bss_free(struct cfg80211_internal_bss *bss)
{
	struct cfg80211_bss_ies *ies;

	if (WARN_ON(atomic_read(&bss->hold)))
		return;

	ies = (void *)rcu_access_pointer(bss->pub.beacon_ies);
	if (ies && !bss->pub.hidden_beacon_bss)
		kfree_rcu(ies, rcu_head);
	ies = (void *)rcu_access_pointer(bss->pub.proberesp_ies);
	if (ies)
		kfree_rcu(ies, rcu_head);

	/*
	 * This happens when the module is removed, it doesn't
	 * really matter any more save for completeness
	 */
	if (!list_empty(&bss->hidden_list))
		list_del(&bss->hidden_list);

	kfree(bss);
}