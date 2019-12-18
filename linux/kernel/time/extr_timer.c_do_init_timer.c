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
struct TYPE_2__ {int /*<<< orphan*/ * pprev; } ;
struct timer_list {void (* function ) (struct timer_list*) ;unsigned int flags; int /*<<< orphan*/  lockdep_map; TYPE_1__ entry; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_init_map (int /*<<< orphan*/ *,char const*,struct lock_class_key*,int /*<<< orphan*/ ) ; 
 unsigned int raw_smp_processor_id () ; 

__attribute__((used)) static void do_init_timer(struct timer_list *timer,
			  void (*func)(struct timer_list *),
			  unsigned int flags,
			  const char *name, struct lock_class_key *key)
{
	timer->entry.pprev = NULL;
	timer->function = func;
	timer->flags = flags | raw_smp_processor_id();
	lockdep_init_map(&timer->lockdep_map, name, key, 0);
}