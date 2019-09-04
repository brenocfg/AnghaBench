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
 int /*<<< orphan*/  VMENTRY_CYCLES ; 
 int /*<<< orphan*/  do_exit ; 
 int /*<<< orphan*/  wait_cycles (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vmentry(void)
{
	if (!do_exit)
		return;
	
	wait_cycles(VMENTRY_CYCLES);
}