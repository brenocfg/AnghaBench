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
struct uncached_list {int /*<<< orphan*/  lock; } ;
struct rtable {int /*<<< orphan*/  rt_uncached; struct uncached_list* rt_uncached_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rt_del_uncached_list(struct rtable *rt)
{
	if (!list_empty(&rt->rt_uncached)) {
		struct uncached_list *ul = rt->rt_uncached_list;

		spin_lock_bh(&ul->lock);
		list_del(&rt->rt_uncached);
		spin_unlock_bh(&ul->lock);
	}
}