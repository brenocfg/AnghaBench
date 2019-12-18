#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_2__* rseq; } ;
struct TYPE_3__ {int /*<<< orphan*/  ptr64; } ;
struct TYPE_4__ {TYPE_1__ rseq_cs; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ clear_user (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int clear_rseq_cs(struct task_struct *t)
{
	/*
	 * The rseq_cs field is set to NULL on preemption or signal
	 * delivery on top of rseq assembly block, as well as on top
	 * of code outside of the rseq assembly block. This performs
	 * a lazy clear of the rseq_cs field.
	 *
	 * Set rseq_cs to NULL.
	 */
	if (clear_user(&t->rseq->rseq_cs.ptr64, sizeof(t->rseq->rseq_cs.ptr64)))
		return -EFAULT;
	return 0;
}