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
struct gnet_dump {scalar_t__ xstats_len; int /*<<< orphan*/ * xstats; scalar_t__ lock; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_64bit (int /*<<< orphan*/ ,int,int,void*,int) ; 
 int /*<<< orphan*/  spin_unlock_bh (scalar_t__) ; 

__attribute__((used)) static inline int
gnet_stats_copy(struct gnet_dump *d, int type, void *buf, int size, int padattr)
{
	if (nla_put_64bit(d->skb, type, size, buf, padattr))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	if (d->lock)
		spin_unlock_bh(d->lock);
	kfree(d->xstats);
	d->xstats = NULL;
	d->xstats_len = 0;
	return -1;
}