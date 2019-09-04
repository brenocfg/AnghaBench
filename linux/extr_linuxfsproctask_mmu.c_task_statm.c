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
struct mm_struct {unsigned long start_code; unsigned long data_vm; unsigned long stack_vm; unsigned long total_vm; int /*<<< orphan*/  end_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  MM_ANONPAGES ; 
 int /*<<< orphan*/  MM_FILEPAGES ; 
 int /*<<< orphan*/  MM_SHMEMPAGES ; 
 unsigned long PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long get_mm_counter (struct mm_struct*,int /*<<< orphan*/ ) ; 

unsigned long task_statm(struct mm_struct *mm,
			 unsigned long *shared, unsigned long *text,
			 unsigned long *data, unsigned long *resident)
{
	*shared = get_mm_counter(mm, MM_FILEPAGES) +
			get_mm_counter(mm, MM_SHMEMPAGES);
	*text = (PAGE_ALIGN(mm->end_code) - (mm->start_code & PAGE_MASK))
								>> PAGE_SHIFT;
	*data = mm->data_vm + mm->stack_vm;
	*resident = *shared + get_mm_counter(mm, MM_ANONPAGES);
	return mm->total_vm;
}