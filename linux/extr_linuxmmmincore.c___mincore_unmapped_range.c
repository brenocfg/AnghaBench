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
struct vm_area_struct {TYPE_1__* vm_file; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  linear_page_index (struct vm_area_struct*,unsigned long) ; 
 unsigned char mincore_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mincore_unmapped_range(unsigned long addr, unsigned long end,
				struct vm_area_struct *vma, unsigned char *vec)
{
	unsigned long nr = (end - addr) >> PAGE_SHIFT;
	int i;

	if (vma->vm_file) {
		pgoff_t pgoff;

		pgoff = linear_page_index(vma, addr);
		for (i = 0; i < nr; i++, pgoff++)
			vec[i] = mincore_page(vma->vm_file->f_mapping, pgoff);
	} else {
		for (i = 0; i < nr; i++)
			vec[i] = 0;
	}
	return nr;
}