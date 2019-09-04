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
struct list_set {int /*<<< orphan*/  gc; } ;
struct ip_set {int /*<<< orphan*/  timeout; struct list_set* data; } ;

/* Variables and functions */
 int HZ ; 
 int IPSET_GC_PERIOD (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,void (*) (struct timer_list*),int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
list_set_gc_init(struct ip_set *set, void (*gc)(struct timer_list *t))
{
	struct list_set *map = set->data;

	timer_setup(&map->gc, gc, 0);
	mod_timer(&map->gc, jiffies + IPSET_GC_PERIOD(set->timeout) * HZ);
}