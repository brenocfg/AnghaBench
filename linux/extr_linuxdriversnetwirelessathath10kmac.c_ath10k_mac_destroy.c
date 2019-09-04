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
struct ieee80211_ops {int dummy; } ;
struct ath10k {int /*<<< orphan*/  hw; struct ieee80211_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_ops*) ; 

void ath10k_mac_destroy(struct ath10k *ar)
{
	struct ieee80211_ops *ops = ar->ops;

	ieee80211_free_hw(ar->hw);
	kfree(ops);
}