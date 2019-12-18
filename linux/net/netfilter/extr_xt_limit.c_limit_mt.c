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
struct xt_rateinfo {scalar_t__ credit_cap; scalar_t__ cost; struct xt_limit_priv* master; } ;
struct xt_limit_priv {scalar_t__ credit; int /*<<< orphan*/  lock; int /*<<< orphan*/  prev; } ;
struct xt_action_param {struct xt_rateinfo* matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned long CREDITS_PER_JIFFY ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned long xchg (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool
limit_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_rateinfo *r = par->matchinfo;
	struct xt_limit_priv *priv = r->master;
	unsigned long now = jiffies;

	spin_lock_bh(&priv->lock);
	priv->credit += (now - xchg(&priv->prev, now)) * CREDITS_PER_JIFFY;
	if (priv->credit > r->credit_cap)
		priv->credit = r->credit_cap;

	if (priv->credit >= r->cost) {
		/* We're not limited. */
		priv->credit -= r->cost;
		spin_unlock_bh(&priv->lock);
		return true;
	}

	spin_unlock_bh(&priv->lock);
	return false;
}