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
struct task_struct {unsigned long kcov_size; struct kcov* kcov; int /*<<< orphan*/  kcov_mode; int /*<<< orphan*/  kcov_area; } ;
struct kcov {void* mode; unsigned long size; struct task_struct* t; int /*<<< orphan*/  area; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int ENOTTY ; 
 int INT_MAX ; 
#define  KCOV_DISABLE 130 
#define  KCOV_ENABLE 129 
#define  KCOV_INIT_TRACE 128 
 void* KCOV_MODE_DISABLED ; 
 void* KCOV_MODE_INIT ; 
 void* KCOV_MODE_TRACE_CMP ; 
 void* KCOV_MODE_TRACE_PC ; 
 unsigned long KCOV_TRACE_CMP ; 
 unsigned long KCOV_TRACE_PC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  barrier () ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  kcov_fault_in_area (struct kcov*) ; 
 int /*<<< orphan*/  kcov_get (struct kcov*) ; 
 int /*<<< orphan*/  kcov_put (struct kcov*) ; 
 int /*<<< orphan*/  kcov_task_init (struct task_struct*) ; 

__attribute__((used)) static int kcov_ioctl_locked(struct kcov *kcov, unsigned int cmd,
			     unsigned long arg)
{
	struct task_struct *t;
	unsigned long size, unused;

	switch (cmd) {
	case KCOV_INIT_TRACE:
		/*
		 * Enable kcov in trace mode and setup buffer size.
		 * Must happen before anything else.
		 */
		if (kcov->mode != KCOV_MODE_DISABLED)
			return -EBUSY;
		/*
		 * Size must be at least 2 to hold current position and one PC.
		 * Later we allocate size * sizeof(unsigned long) memory,
		 * that must not overflow.
		 */
		size = arg;
		if (size < 2 || size > INT_MAX / sizeof(unsigned long))
			return -EINVAL;
		kcov->size = size;
		kcov->mode = KCOV_MODE_INIT;
		return 0;
	case KCOV_ENABLE:
		/*
		 * Enable coverage for the current task.
		 * At this point user must have been enabled trace mode,
		 * and mmapped the file. Coverage collection is disabled only
		 * at task exit or voluntary by KCOV_DISABLE. After that it can
		 * be enabled for another task.
		 */
		if (kcov->mode != KCOV_MODE_INIT || !kcov->area)
			return -EINVAL;
		t = current;
		if (kcov->t != NULL || t->kcov != NULL)
			return -EBUSY;
		if (arg == KCOV_TRACE_PC)
			kcov->mode = KCOV_MODE_TRACE_PC;
		else if (arg == KCOV_TRACE_CMP)
#ifdef CONFIG_KCOV_ENABLE_COMPARISONS
			kcov->mode = KCOV_MODE_TRACE_CMP;
#else
		return -ENOTSUPP;
#endif
		else
			return -EINVAL;
		kcov_fault_in_area(kcov);
		/* Cache in task struct for performance. */
		t->kcov_size = kcov->size;
		t->kcov_area = kcov->area;
		/* See comment in check_kcov_mode(). */
		barrier();
		WRITE_ONCE(t->kcov_mode, kcov->mode);
		t->kcov = kcov;
		kcov->t = t;
		/* This is put either in kcov_task_exit() or in KCOV_DISABLE. */
		kcov_get(kcov);
		return 0;
	case KCOV_DISABLE:
		/* Disable coverage for the current task. */
		unused = arg;
		if (unused != 0 || current->kcov != kcov)
			return -EINVAL;
		t = current;
		if (WARN_ON(kcov->t != t))
			return -EINVAL;
		kcov_task_init(t);
		kcov->t = NULL;
		kcov->mode = KCOV_MODE_INIT;
		kcov_put(kcov);
		return 0;
	default:
		return -ENOTTY;
	}
}