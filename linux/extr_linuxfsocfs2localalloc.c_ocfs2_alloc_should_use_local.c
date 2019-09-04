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
typedef  int u64 ;
struct ocfs2_super {int local_alloc_bits; int /*<<< orphan*/  osb_lock; int /*<<< orphan*/  local_alloc_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_la_state_enabled (struct ocfs2_super*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_alloc_should_use_local (unsigned long long,int /*<<< orphan*/ ,int,int) ; 

int ocfs2_alloc_should_use_local(struct ocfs2_super *osb, u64 bits)
{
	int ret = 0;
	int la_bits;

	spin_lock(&osb->osb_lock);
	la_bits = osb->local_alloc_bits;

	if (!ocfs2_la_state_enabled(osb))
		goto bail;

	/* la_bits should be at least twice the size (in clusters) of
	 * a new block group. We want to be sure block group
	 * allocations go through the local alloc, so allow an
	 * allocation to take up to half the bitmap. */
	if (bits > (la_bits / 2))
		goto bail;

	ret = 1;
bail:
	trace_ocfs2_alloc_should_use_local(
	     (unsigned long long)bits, osb->local_alloc_state, la_bits, ret);
	spin_unlock(&osb->osb_lock);
	return ret;
}