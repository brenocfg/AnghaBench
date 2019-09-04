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
struct vaddr_range {unsigned long start; unsigned long end; } ;

/* Variables and functions */

__attribute__((used)) static inline int vaddr_in_range(unsigned long vaddr, struct vaddr_range *r)
{
	if (vaddr < r->start)
		return 0;
	if (vaddr >= r->end)
		return 0;
	return 1;
}