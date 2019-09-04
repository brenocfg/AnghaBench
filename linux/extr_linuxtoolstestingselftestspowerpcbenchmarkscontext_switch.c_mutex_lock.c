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
 int FUTEX_WAIT ; 
 int cmpxchg (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  processes ; 
 int /*<<< orphan*/  sys_futex (unsigned long*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xchg (unsigned long*,int) ; 

__attribute__((used)) static int mutex_lock(unsigned long *m)
{
	int c;
	int flags = FUTEX_WAIT;
	if (!processes)
		flags |= FUTEX_PRIVATE_FLAG;

	c = cmpxchg(m, 0, 1);
	if (!c)
		return 0;

	if (c == 1)
		c = xchg(m, 2);

	while (c) {
		sys_futex(m, flags, 2, NULL, NULL, 0);
		c = xchg(m, 2);
	}

	return 0;
}