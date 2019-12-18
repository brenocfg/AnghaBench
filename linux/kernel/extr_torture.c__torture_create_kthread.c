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
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  VERBOSE_TOROUT_ERRSTRING (char*) ; 
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 struct task_struct* kthread_run (int (*) (void*),void*,char*,char*) ; 
 int /*<<< orphan*/  torture_shuffle_task_register (struct task_struct*) ; 

int _torture_create_kthread(int (*fn)(void *arg), void *arg, char *s, char *m,
			    char *f, struct task_struct **tp)
{
	int ret = 0;

	VERBOSE_TOROUT_STRING(m);
	*tp = kthread_run(fn, arg, "%s", s);
	if (IS_ERR(*tp)) {
		ret = PTR_ERR(*tp);
		VERBOSE_TOROUT_ERRSTRING(f);
		*tp = NULL;
	}
	torture_shuffle_task_register(*tp);
	return ret;
}