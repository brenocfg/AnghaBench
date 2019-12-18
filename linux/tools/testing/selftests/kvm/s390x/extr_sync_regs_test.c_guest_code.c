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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_SYNC (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void guest_code(void)
{
	register u64 stage asm("11") = 0;

	for (;;) {
		GUEST_SYNC(0);
		asm volatile ("ahi %0,1" : : "r"(stage));
	}
}