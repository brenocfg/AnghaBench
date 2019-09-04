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

/* Variables and functions */
#define  RECORD_CMDLINE 129 
#define  RECORD_TGID 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sched_cmdline_ref ; 
 int /*<<< orphan*/  sched_register_mutex ; 
 scalar_t__ sched_tgid_ref ; 
 int /*<<< orphan*/  tracing_sched_register () ; 

__attribute__((used)) static void tracing_start_sched_switch(int ops)
{
	bool sched_register = (!sched_cmdline_ref && !sched_tgid_ref);
	mutex_lock(&sched_register_mutex);

	switch (ops) {
	case RECORD_CMDLINE:
		sched_cmdline_ref++;
		break;

	case RECORD_TGID:
		sched_tgid_ref++;
		break;
	}

	if (sched_register && (sched_cmdline_ref || sched_tgid_ref))
		tracing_sched_register();
	mutex_unlock(&sched_register_mutex);
}