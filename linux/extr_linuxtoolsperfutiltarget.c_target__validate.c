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
struct target {int system_wide; int per_thread; int /*<<< orphan*/ * cpu_list; int /*<<< orphan*/ * uid_str; scalar_t__ tid; scalar_t__ pid; } ;
typedef  enum target_errno { ____Placeholder_target_errno } target_errno ;

/* Variables and functions */
 int TARGET_ERRNO__PID_OVERRIDE_CPU ; 
 int TARGET_ERRNO__PID_OVERRIDE_SYSTEM ; 
 int TARGET_ERRNO__PID_OVERRIDE_UID ; 
 int TARGET_ERRNO__SUCCESS ; 
 int TARGET_ERRNO__SYSTEM_OVERRIDE_THREAD ; 
 int TARGET_ERRNO__UID_OVERRIDE_CPU ; 
 int TARGET_ERRNO__UID_OVERRIDE_SYSTEM ; 

enum target_errno target__validate(struct target *target)
{
	enum target_errno ret = TARGET_ERRNO__SUCCESS;

	if (target->pid)
		target->tid = target->pid;

	/* CPU and PID are mutually exclusive */
	if (target->tid && target->cpu_list) {
		target->cpu_list = NULL;
		if (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__PID_OVERRIDE_CPU;
	}

	/* UID and PID are mutually exclusive */
	if (target->tid && target->uid_str) {
		target->uid_str = NULL;
		if (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__PID_OVERRIDE_UID;
	}

	/* UID and CPU are mutually exclusive */
	if (target->uid_str && target->cpu_list) {
		target->cpu_list = NULL;
		if (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__UID_OVERRIDE_CPU;
	}

	/* PID and SYSTEM are mutually exclusive */
	if (target->tid && target->system_wide) {
		target->system_wide = false;
		if (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__PID_OVERRIDE_SYSTEM;
	}

	/* UID and SYSTEM are mutually exclusive */
	if (target->uid_str && target->system_wide) {
		target->system_wide = false;
		if (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__UID_OVERRIDE_SYSTEM;
	}

	/* THREAD and SYSTEM/CPU are mutually exclusive */
	if (target->per_thread && (target->system_wide || target->cpu_list)) {
		target->per_thread = false;
		if (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__SYSTEM_OVERRIDE_THREAD;
	}

	return ret;
}