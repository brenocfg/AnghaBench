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
struct task_struct {int dummy; } ;
typedef  enum hk_flags { ____Placeholder_hk_flags } hk_flags ;

/* Variables and functions */
 int housekeeping_flags ; 
 int /*<<< orphan*/  housekeeping_mask ; 
 int /*<<< orphan*/  housekeeping_overridden ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 

void housekeeping_affine(struct task_struct *t, enum hk_flags flags)
{
	if (static_branch_unlikely(&housekeeping_overridden))
		if (housekeeping_flags & flags)
			set_cpus_allowed_ptr(t, housekeeping_mask);
}