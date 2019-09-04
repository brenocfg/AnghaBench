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
struct task_struct {scalar_t__ maj_flt; scalar_t__ min_flt; scalar_t__ nivcsw; scalar_t__ nvcsw; } ;
struct rusage {int /*<<< orphan*/  ru_oublock; int /*<<< orphan*/  ru_inblock; int /*<<< orphan*/  ru_majflt; int /*<<< orphan*/  ru_minflt; int /*<<< orphan*/  ru_nivcsw; int /*<<< orphan*/  ru_nvcsw; } ;

/* Variables and functions */
 scalar_t__ task_io_get_inblock (struct task_struct*) ; 
 scalar_t__ task_io_get_oublock (struct task_struct*) ; 

__attribute__((used)) static void accumulate_thread_rusage(struct task_struct *t, struct rusage *r)
{
	r->ru_nvcsw += t->nvcsw;
	r->ru_nivcsw += t->nivcsw;
	r->ru_minflt += t->min_flt;
	r->ru_majflt += t->maj_flt;
	r->ru_inblock += task_io_get_inblock(t);
	r->ru_oublock += task_io_get_oublock(t);
}