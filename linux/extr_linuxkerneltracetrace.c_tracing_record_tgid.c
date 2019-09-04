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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_RECORD_TGID ; 
 int /*<<< orphan*/  tracing_record_taskinfo (struct task_struct*,int /*<<< orphan*/ ) ; 

void tracing_record_tgid(struct task_struct *task)
{
	tracing_record_taskinfo(task, TRACE_RECORD_TGID);
}