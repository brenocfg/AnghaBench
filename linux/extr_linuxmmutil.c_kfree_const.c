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
 int /*<<< orphan*/  is_kernel_rodata (unsigned long) ; 
 int /*<<< orphan*/  kfree (void const*) ; 

void kfree_const(const void *x)
{
	if (!is_kernel_rodata((unsigned long)x))
		kfree(x);
}