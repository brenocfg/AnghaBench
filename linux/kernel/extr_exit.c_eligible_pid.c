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
struct wait_opts {scalar_t__ wo_type; scalar_t__ wo_pid; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ PIDTYPE_MAX ; 
 scalar_t__ task_pid_type (struct task_struct*,scalar_t__) ; 

__attribute__((used)) static int eligible_pid(struct wait_opts *wo, struct task_struct *p)
{
	return	wo->wo_type == PIDTYPE_MAX ||
		task_pid_type(p, wo->wo_type) == wo->wo_pid;
}