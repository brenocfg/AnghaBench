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
 int FUTEX_PRIVATE_FLAG ; 
 int FUTEX_WAKE ; 
 int /*<<< orphan*/  processes ; 
 int /*<<< orphan*/  sys_futex (unsigned long*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xchg (unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mutex_unlock(unsigned long *m)
{
	int flags = FUTEX_WAKE;
	if (!processes)
		flags |= FUTEX_PRIVATE_FLAG;

	if (*m == 2)
		*m = 0;
	else if (xchg(m, 0) == 1)
		return 0;

	sys_futex(m, flags, 1, NULL, NULL, 0);

	return 0;
}