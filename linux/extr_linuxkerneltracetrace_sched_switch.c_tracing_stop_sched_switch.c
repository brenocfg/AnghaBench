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
 int /*<<< orphan*/  sched_cmdline_ref ; 
 int /*<<< orphan*/  sched_register_mutex ; 
 int /*<<< orphan*/  sched_tgid_ref ; 
 int /*<<< orphan*/  tracing_sched_unregister () ; 

__attribute__((used)) static void tracing_stop_sched_switch(int ops)
{
	mutex_lock(&sched_register_mutex);

	switch (ops) {
	case RECORD_CMDLINE:
		sched_cmdline_ref--;
		break;

	case RECORD_TGID:
		sched_tgid_ref--;
		break;
	}

	if (!sched_cmdline_ref && !sched_tgid_ref)
		tracing_sched_unregister();
	mutex_unlock(&sched_register_mutex);
}