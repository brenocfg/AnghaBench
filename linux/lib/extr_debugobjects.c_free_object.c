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
struct debug_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODEBUG_FREE_WORK_DELAY ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __free_object (struct debug_obj*) ; 
 int /*<<< orphan*/  debug_obj_work ; 
 int /*<<< orphan*/  obj_freeing ; 
 scalar_t__ obj_nr_tofree ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_object(struct debug_obj *obj)
{
	__free_object(obj);
	if (!obj_freeing && obj_nr_tofree) {
		WRITE_ONCE(obj_freeing, true);
		schedule_delayed_work(&debug_obj_work, ODEBUG_FREE_WORK_DELAY);
	}
}