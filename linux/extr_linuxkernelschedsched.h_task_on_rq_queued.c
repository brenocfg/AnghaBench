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
struct task_struct {scalar_t__ on_rq; } ;

/* Variables and functions */
 scalar_t__ TASK_ON_RQ_QUEUED ; 

__attribute__((used)) static inline int task_on_rq_queued(struct task_struct *p)
{
	return p->on_rq == TASK_ON_RQ_QUEUED;
}