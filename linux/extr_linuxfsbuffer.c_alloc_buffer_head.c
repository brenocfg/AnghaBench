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
struct buffer_head {int /*<<< orphan*/  b_assoc_buffers; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 TYPE_1__ bh_accounting ; 
 int /*<<< orphan*/  bh_cachep ; 
 struct buffer_head* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  recalc_bh_state () ; 

struct buffer_head *alloc_buffer_head(gfp_t gfp_flags)
{
	struct buffer_head *ret = kmem_cache_zalloc(bh_cachep, gfp_flags);
	if (ret) {
		INIT_LIST_HEAD(&ret->b_assoc_buffers);
		preempt_disable();
		__this_cpu_inc(bh_accounting.nr);
		recalc_bh_state();
		preempt_enable();
	}
	return ret;
}