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
struct mm_struct {int /*<<< orphan*/  core_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_put_decimal_ull (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static inline void task_core_dumping(struct seq_file *m, struct mm_struct *mm)
{
	seq_put_decimal_ull(m, "CoreDumping:\t", !!mm->core_state);
	seq_putc(m, '\n');
}