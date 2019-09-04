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
 int brk (void*) ; 
 int /*<<< orphan*/  done ; 
 void* sbrk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kernel_loop(void)
{
	void *addr = sbrk(0);
	int err = 0;

	while (!done && !err) {
		err = brk(addr + 4096);
		err |= brk(addr);
	}
}