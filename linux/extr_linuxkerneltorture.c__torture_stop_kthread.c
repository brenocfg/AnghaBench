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
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 

void _torture_stop_kthread(char *m, struct task_struct **tp)
{
	if (*tp == NULL)
		return;
	VERBOSE_TOROUT_STRING(m);
	kthread_stop(*tp);
	*tp = NULL;
}