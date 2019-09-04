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
struct ida_bitmap {int dummy; } ;
struct ida {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDA_PRELOAD_SIZE ; 
 int /*<<< orphan*/  __radix_tree_preload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_bitmap ; 
 int /*<<< orphan*/  kfree (struct ida_bitmap*) ; 
 struct ida_bitmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ this_cpu_cmpxchg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ida_bitmap*) ; 
 int /*<<< orphan*/  this_cpu_read (int /*<<< orphan*/ ) ; 

int ida_pre_get(struct ida *ida, gfp_t gfp)
{
	/*
	 * The IDA API has no preload_end() equivalent.  Instead,
	 * ida_get_new() can return -EAGAIN, prompting the caller
	 * to return to the ida_pre_get() step.
	 */
	if (!__radix_tree_preload(gfp, IDA_PRELOAD_SIZE))
		preempt_enable();

	if (!this_cpu_read(ida_bitmap)) {
		struct ida_bitmap *bitmap = kzalloc(sizeof(*bitmap), gfp);
		if (!bitmap)
			return 0;
		if (this_cpu_cmpxchg(ida_bitmap, NULL, bitmap))
			kfree(bitmap);
	}

	return 1;
}