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
struct logic_pio_hwaddr {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_range_mutex ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void logic_pio_unregister_range(struct logic_pio_hwaddr *range)
{
	mutex_lock(&io_range_mutex);
	list_del_rcu(&range->list);
	mutex_unlock(&io_range_mutex);
	synchronize_rcu();
}