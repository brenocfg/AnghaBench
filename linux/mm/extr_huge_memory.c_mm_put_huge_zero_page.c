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
struct mm_struct {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMF_HUGE_ZERO_PAGE ; 
 int /*<<< orphan*/  put_huge_zero_page () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mm_put_huge_zero_page(struct mm_struct *mm)
{
	if (test_bit(MMF_HUGE_ZERO_PAGE, &mm->flags))
		put_huge_zero_page();
}