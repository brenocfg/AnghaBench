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
struct tipc_member {TYPE_1__* group; int /*<<< orphan*/  small_win; } ;
struct TYPE_2__ {int* open; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tipc_group_open(struct tipc_member *m, bool *wakeup)
{
	*wakeup = false;
	if (list_empty(&m->small_win))
		return;
	list_del_init(&m->small_win);
	*m->group->open = true;
	*wakeup = true;
}