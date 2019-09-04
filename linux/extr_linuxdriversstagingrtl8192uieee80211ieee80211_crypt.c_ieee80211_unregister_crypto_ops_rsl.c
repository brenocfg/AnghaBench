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
struct list_head {struct list_head* next; } ;
struct ieee80211_crypto_ops {int /*<<< orphan*/  name; } ;
struct ieee80211_crypto_alg {int /*<<< orphan*/  list; struct ieee80211_crypto_ops* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct list_head algs; } ;

/* Variables and functions */
 TYPE_1__* hcrypt ; 
 int /*<<< orphan*/  kfree (struct ieee80211_crypto_alg*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ieee80211_unregister_crypto_ops(struct ieee80211_crypto_ops *ops)
{
	unsigned long flags;
	struct list_head *ptr;
	struct ieee80211_crypto_alg *del_alg = NULL;

	if (!hcrypt)
		return -1;

	spin_lock_irqsave(&hcrypt->lock, flags);
	for (ptr = hcrypt->algs.next; ptr != &hcrypt->algs; ptr = ptr->next) {
		struct ieee80211_crypto_alg *alg =
			(struct ieee80211_crypto_alg *)ptr;
		if (alg->ops == ops) {
			list_del(&alg->list);
			del_alg = alg;
			break;
		}
	}
	spin_unlock_irqrestore(&hcrypt->lock, flags);

	if (del_alg) {
		pr_debug("ieee80211_crypt: unregistered algorithm '%s'\n",
				ops->name);
		kfree(del_alg);
	}

	return del_alg ? 0 : -1;
}