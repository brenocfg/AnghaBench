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
struct seq_file {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  hugetlb_usage; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

void hugetlb_report_usage(struct seq_file *m, struct mm_struct *mm)
{
	seq_printf(m, "HugetlbPages:\t%8lu kB\n",
		   atomic_long_read(&mm->hugetlb_usage) << (PAGE_SHIFT - 10));
}