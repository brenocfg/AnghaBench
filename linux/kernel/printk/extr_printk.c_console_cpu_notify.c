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
 scalar_t__ console_trylock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  cpuhp_tasks_frozen ; 

__attribute__((used)) static int console_cpu_notify(unsigned int cpu)
{
	if (!cpuhp_tasks_frozen) {
		/* If trylock fails, someone else is doing the printing */
		if (console_trylock())
			console_unlock();
	}
	return 0;
}