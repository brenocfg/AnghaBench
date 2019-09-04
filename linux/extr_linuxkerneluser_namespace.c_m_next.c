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
struct seq_file {TYPE_1__* op; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {void* (* start ) (struct seq_file*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 void* stub1 (struct seq_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *m_next(struct seq_file *seq, void *v, loff_t *pos)
{
	(*pos)++;
	return seq->op->start(seq, pos);
}