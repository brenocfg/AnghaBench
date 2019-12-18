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
struct sk_buff {int dummy; } ;
struct gnet_dump {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int gnet_stats_start_copy_compat (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gnet_dump*,int) ; 

int
gnet_stats_start_copy(struct sk_buff *skb, int type, spinlock_t *lock,
		      struct gnet_dump *d, int padattr)
{
	return gnet_stats_start_copy_compat(skb, type, 0, 0, lock, d, padattr);
}