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
struct mm_walk {int /*<<< orphan*/  private; int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 scalar_t__ __mincore_unmapped_range (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mincore_unmapped_range(unsigned long addr, unsigned long end,
				   struct mm_walk *walk)
{
	walk->private += __mincore_unmapped_range(addr, end,
						  walk->vma, walk->private);
	return 0;
}