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
struct kcov {unsigned long* area; unsigned long size; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  READ_ONCE (unsigned long) ; 

__attribute__((used)) static void kcov_fault_in_area(struct kcov *kcov)
{
	unsigned long stride = PAGE_SIZE / sizeof(unsigned long);
	unsigned long *area = kcov->area;
	unsigned long offset;

	for (offset = 0; offset < kcov->size; offset += stride)
		READ_ONCE(area[offset]);
}