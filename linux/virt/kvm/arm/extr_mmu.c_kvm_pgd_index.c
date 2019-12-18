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
 unsigned long PGDIR_SHIFT ; 

__attribute__((used)) static unsigned int kvm_pgd_index(unsigned long addr, unsigned int ptrs_per_pgd)
{
	return (addr >> PGDIR_SHIFT) & (ptrs_per_pgd - 1);
}