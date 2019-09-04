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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct list_set {TYPE_1__ gc; struct ip_set* set; } ;
struct ip_set {int /*<<< orphan*/  timeout; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int HZ ; 
 int IPSET_GC_PERIOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct list_set* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc ; 
 scalar_t__ jiffies ; 
 struct list_set* map ; 
 int /*<<< orphan*/  set_cleanup_entries (struct ip_set*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
list_set_gc(struct timer_list *t)
{
	struct list_set *map = from_timer(map, t, gc);
	struct ip_set *set = map->set;

	spin_lock_bh(&set->lock);
	set_cleanup_entries(set);
	spin_unlock_bh(&set->lock);

	map->gc.expires = jiffies + IPSET_GC_PERIOD(set->timeout) * HZ;
	add_timer(&map->gc);
}