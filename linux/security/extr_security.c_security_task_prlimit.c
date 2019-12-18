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
struct cred {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,struct cred const*,unsigned int) ; 
 int /*<<< orphan*/  task_prlimit ; 

int security_task_prlimit(const struct cred *cred, const struct cred *tcred,
			  unsigned int flags)
{
	return call_int_hook(task_prlimit, 0, cred, tcred, flags);
}