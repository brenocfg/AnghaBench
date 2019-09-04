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
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 scalar_t__ rlimit (int /*<<< orphan*/ ) ; 

bool can_do_mlock(void)
{
	if (rlimit(RLIMIT_MEMLOCK) != 0)
		return true;
	if (capable(CAP_IPC_LOCK))
		return true;
	return false;
}