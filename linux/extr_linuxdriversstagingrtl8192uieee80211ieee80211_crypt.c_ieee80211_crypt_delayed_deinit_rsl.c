#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct ieee80211_device {int /*<<< orphan*/  lock; TYPE_1__ crypt_deinit_timer; int /*<<< orphan*/  crypt_deinit_list; } ;
struct ieee80211_crypt_data {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

void ieee80211_crypt_delayed_deinit(struct ieee80211_device *ieee,
				    struct ieee80211_crypt_data **crypt)
{
	struct ieee80211_crypt_data *tmp;
	unsigned long flags;

	if (!(*crypt))
		return;

	tmp = *crypt;
	*crypt = NULL;

	/* must not run ops->deinit() while there may be pending encrypt or
	 * decrypt operations. Use a list of delayed deinits to avoid needing
	 * locking.
	 */

	spin_lock_irqsave(&ieee->lock, flags);
	list_add(&tmp->list, &ieee->crypt_deinit_list);
	if (!timer_pending(&ieee->crypt_deinit_timer)) {
		ieee->crypt_deinit_timer.expires = jiffies + HZ;
		add_timer(&ieee->crypt_deinit_timer);
	}
	spin_unlock_irqrestore(&ieee->lock, flags);
}