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
struct kernel_clone_args {int flags; } ;

/* Variables and functions */
 int CLONE_PARENT_SETTID ; 
 int CLONE_PIDFD ; 

bool legacy_clone_args_valid(const struct kernel_clone_args *kargs)
{
	/* clone(CLONE_PIDFD) uses parent_tidptr to return a pidfd */
	if ((kargs->flags & CLONE_PIDFD) &&
	    (kargs->flags & CLONE_PARENT_SETTID))
		return false;

	return true;
}