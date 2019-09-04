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
struct conntrack_gc_work {int exiting; int /*<<< orphan*/  next_gc_run; int /*<<< orphan*/  dwork; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_worker ; 

__attribute__((used)) static void conntrack_gc_work_init(struct conntrack_gc_work *gc_work)
{
	INIT_DEFERRABLE_WORK(&gc_work->dwork, gc_worker);
	gc_work->next_gc_run = HZ;
	gc_work->exiting = false;
}