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
struct vm_area_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zap_page_range (struct vm_area_struct*,unsigned long,unsigned long) ; 

__attribute__((used)) static long madvise_dontneed_single_vma(struct vm_area_struct *vma,
					unsigned long start, unsigned long end)
{
	zap_page_range(vma, start, end - start);
	return 0;
}