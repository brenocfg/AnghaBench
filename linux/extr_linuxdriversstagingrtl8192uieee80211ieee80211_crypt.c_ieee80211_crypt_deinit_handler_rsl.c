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
struct timer_list {int dummy; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct ieee80211_device {int /*<<< orphan*/  lock; TYPE_2__ crypt_deinit_timer; TYPE_1__* dev; int /*<<< orphan*/  crypt_deinit_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  crypt_deinit_timer ; 
 struct ieee80211_device* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ieee80211_device* ieee ; 
 int /*<<< orphan*/  ieee80211_crypt_deinit_entries (struct ieee80211_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ieee80211_crypt_deinit_handler(struct timer_list *t)
{
	struct ieee80211_device *ieee = from_timer(ieee, t, crypt_deinit_timer);
	unsigned long flags;

	spin_lock_irqsave(&ieee->lock, flags);
	ieee80211_crypt_deinit_entries(ieee, 0);
	if (!list_empty(&ieee->crypt_deinit_list)) {
		netdev_dbg(ieee->dev, "%s: entries remaining in delayed crypt deletion list\n",
				ieee->dev->name);
		ieee->crypt_deinit_timer.expires = jiffies + HZ;
		add_timer(&ieee->crypt_deinit_timer);
	}
	spin_unlock_irqrestore(&ieee->lock, flags);

}