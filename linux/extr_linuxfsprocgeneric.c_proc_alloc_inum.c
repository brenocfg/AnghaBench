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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PROC_DYNAMIC_FIRST ; 
 scalar_t__ UINT_MAX ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_inum_ida ; 

int proc_alloc_inum(unsigned int *inum)
{
	int i;

	i = ida_simple_get(&proc_inum_ida, 0, UINT_MAX - PROC_DYNAMIC_FIRST + 1,
			   GFP_KERNEL);
	if (i < 0)
		return i;

	*inum = PROC_DYNAMIC_FIRST + (unsigned int)i;
	return 0;
}