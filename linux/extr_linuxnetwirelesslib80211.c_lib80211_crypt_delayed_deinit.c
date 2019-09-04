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
struct lib80211_crypt_info {int /*<<< orphan*/  lock; TYPE_1__ crypt_deinit_timer; int /*<<< orphan*/  crypt_deinit_list; int /*<<< orphan*/  crypt_quiesced; } ;
struct lib80211_crypt_data {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

void lib80211_crypt_delayed_deinit(struct lib80211_crypt_info *info,
				    struct lib80211_crypt_data **crypt)
{
	struct lib80211_crypt_data *tmp;
	unsigned long flags;

	if (*crypt == NULL)
		return;

	tmp = *crypt;
	*crypt = NULL;

	/* must not run ops->deinit() while there may be pending encrypt or
	 * decrypt operations. Use a list of delayed deinits to avoid needing
	 * locking. */

	spin_lock_irqsave(info->lock, flags);
	if (!info->crypt_quiesced) {
		list_add(&tmp->list, &info->crypt_deinit_list);
		if (!timer_pending(&info->crypt_deinit_timer)) {
			info->crypt_deinit_timer.expires = jiffies + HZ;
			add_timer(&info->crypt_deinit_timer);
		}
	}
	spin_unlock_irqrestore(info->lock, flags);
}