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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  find_idr ; 
 int /*<<< orphan*/  idr_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_register_thread () ; 
 int /*<<< orphan*/  rcu_unregister_thread () ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_mk_value (int) ; 

__attribute__((used)) static void *idr_throbber(void *arg)
{
	time_t start = time(NULL);
	int id = *(int *)arg;

	rcu_register_thread();
	do {
		idr_alloc(&find_idr, xa_mk_value(id), id, id + 1, GFP_KERNEL);
		idr_remove(&find_idr, id);
	} while (time(NULL) < start + 10);
	rcu_unregister_thread();

	return NULL;
}