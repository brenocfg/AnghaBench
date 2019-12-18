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
struct mutex_waiter {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  MUTEX_DEBUG_FREE ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mutex_waiter*,int /*<<< orphan*/ ,int) ; 

void debug_mutex_free_waiter(struct mutex_waiter *waiter)
{
	DEBUG_LOCKS_WARN_ON(!list_empty(&waiter->list));
	memset(waiter, MUTEX_DEBUG_FREE, sizeof(*waiter));
}