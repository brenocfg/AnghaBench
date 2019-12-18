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
 scalar_t__ CACHELINE_SIZE ; 
 int /*<<< orphan*/  getppid () ; 
 int /*<<< orphan*/  load (char*) ; 

__attribute__((used)) static void syscall_loop(char *p, unsigned long iterations,
			 unsigned long zero_size)
{
	for (unsigned long i = 0; i < iterations; i++) {
		for (unsigned long j = 0; j < zero_size; j += CACHELINE_SIZE)
			load(p + j);
		getppid();
	}
}