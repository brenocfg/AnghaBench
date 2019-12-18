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
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NR_CPUS ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAX_NR_ZONES ; 
 int /*<<< orphan*/  NR_CPUS_BITS ; 
 int /*<<< orphan*/  NR_PAGEFLAGS ; 
 int /*<<< orphan*/  SPINLOCK_SIZE ; 
 int __MAX_NR_ZONES ; 
 int __NR_PAGEFLAGS ; 
 int ilog2 (int /*<<< orphan*/ ) ; 

int main(void)
{
	/* The enum constants to put into include/generated/bounds.h */
	DEFINE(NR_PAGEFLAGS, __NR_PAGEFLAGS);
	DEFINE(MAX_NR_ZONES, __MAX_NR_ZONES);
#ifdef CONFIG_SMP
	DEFINE(NR_CPUS_BITS, ilog2(CONFIG_NR_CPUS));
#endif
	DEFINE(SPINLOCK_SIZE, sizeof(spinlock_t));
	/* End of constants */

	return 0;
}