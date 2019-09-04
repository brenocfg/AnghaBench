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
struct ieee80211_low_level_stats {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct b43legacy_wl {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  ieee_stats; } ;

/* Variables and functions */
 struct b43legacy_wl* hw_to_b43legacy_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_low_level_stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int b43legacy_op_get_stats(struct ieee80211_hw *hw,
				  struct ieee80211_low_level_stats *stats)
{
	struct b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	unsigned long flags;

	spin_lock_irqsave(&wl->irq_lock, flags);
	memcpy(stats, &wl->ieee_stats, sizeof(*stats));
	spin_unlock_irqrestore(&wl->irq_lock, flags);

	return 0;
}