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
struct mm_struct {unsigned long total_vm; unsigned long hiwater_vm; unsigned long hiwater_rss; unsigned long start_code; unsigned long exec_vm; unsigned long locked_vm; unsigned long data_vm; unsigned long stack_vm; int /*<<< orphan*/  pinned_vm; int /*<<< orphan*/  end_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  MM_ANONPAGES ; 
 int /*<<< orphan*/  MM_FILEPAGES ; 
 int /*<<< orphan*/  MM_SHMEMPAGES ; 
 int /*<<< orphan*/  MM_SWAPENTS ; 
 unsigned long PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  SEQ_PUT_DEC (char*,unsigned long) ; 
 unsigned long atomic64_read (int /*<<< orphan*/ *) ; 
 unsigned long get_mm_counter (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugetlb_report_usage (struct seq_file*,struct mm_struct*) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int mm_pgtables_bytes (struct mm_struct*) ; 
 int /*<<< orphan*/  seq_put_decimal_ull_width (struct seq_file*,char*,int,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

void task_mem(struct seq_file *m, struct mm_struct *mm)
{
	unsigned long text, lib, swap, anon, file, shmem;
	unsigned long hiwater_vm, total_vm, hiwater_rss, total_rss;

	anon = get_mm_counter(mm, MM_ANONPAGES);
	file = get_mm_counter(mm, MM_FILEPAGES);
	shmem = get_mm_counter(mm, MM_SHMEMPAGES);

	/*
	 * Note: to minimize their overhead, mm maintains hiwater_vm and
	 * hiwater_rss only when about to *lower* total_vm or rss.  Any
	 * collector of these hiwater stats must therefore get total_vm
	 * and rss too, which will usually be the higher.  Barriers? not
	 * worth the effort, such snapshots can always be inconsistent.
	 */
	hiwater_vm = total_vm = mm->total_vm;
	if (hiwater_vm < mm->hiwater_vm)
		hiwater_vm = mm->hiwater_vm;
	hiwater_rss = total_rss = anon + file + shmem;
	if (hiwater_rss < mm->hiwater_rss)
		hiwater_rss = mm->hiwater_rss;

	/* split executable areas between text and lib */
	text = PAGE_ALIGN(mm->end_code) - (mm->start_code & PAGE_MASK);
	text = min(text, mm->exec_vm << PAGE_SHIFT);
	lib = (mm->exec_vm << PAGE_SHIFT) - text;

	swap = get_mm_counter(mm, MM_SWAPENTS);
	SEQ_PUT_DEC("VmPeak:\t", hiwater_vm);
	SEQ_PUT_DEC(" kB\nVmSize:\t", total_vm);
	SEQ_PUT_DEC(" kB\nVmLck:\t", mm->locked_vm);
	SEQ_PUT_DEC(" kB\nVmPin:\t", atomic64_read(&mm->pinned_vm));
	SEQ_PUT_DEC(" kB\nVmHWM:\t", hiwater_rss);
	SEQ_PUT_DEC(" kB\nVmRSS:\t", total_rss);
	SEQ_PUT_DEC(" kB\nRssAnon:\t", anon);
	SEQ_PUT_DEC(" kB\nRssFile:\t", file);
	SEQ_PUT_DEC(" kB\nRssShmem:\t", shmem);
	SEQ_PUT_DEC(" kB\nVmData:\t", mm->data_vm);
	SEQ_PUT_DEC(" kB\nVmStk:\t", mm->stack_vm);
	seq_put_decimal_ull_width(m,
		    " kB\nVmExe:\t", text >> 10, 8);
	seq_put_decimal_ull_width(m,
		    " kB\nVmLib:\t", lib >> 10, 8);
	seq_put_decimal_ull_width(m,
		    " kB\nVmPTE:\t", mm_pgtables_bytes(mm) >> 10, 8);
	SEQ_PUT_DEC(" kB\nVmSwap:\t", swap);
	seq_puts(m, " kB\n");
	hugetlb_report_usage(m, mm);
}