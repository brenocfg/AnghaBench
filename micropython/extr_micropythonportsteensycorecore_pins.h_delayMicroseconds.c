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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ n ; 

__attribute__((used)) static inline void delayMicroseconds(uint32_t usec)
{
#if F_CPU == 168000000
	uint32_t n = usec * 56;
#elif F_CPU == 144000000
	uint32_t n = usec * 48;
#elif F_CPU == 120000000
	uint32_t n = usec * 40;
#elif F_CPU == 96000000
	uint32_t n = usec << 5;
#elif F_CPU == 72000000
	uint32_t n = usec * 24;
#elif F_CPU == 48000000
	uint32_t n = usec << 4;
#elif F_CPU == 24000000
	uint32_t n = usec << 3;
#elif F_CPU == 16000000
	uint32_t n = usec << 2;
#elif F_CPU == 8000000
	uint32_t n = usec << 1;
#elif F_CPU == 4000000
	uint32_t n = usec;
#elif F_CPU == 2000000
	uint32_t n = usec >> 1;
#endif
    // changed because a delay of 1 micro Sec @ 2MHz will be 0
	if (n == 0) return;
	__asm__ volatile(
		"L_%=_delayMicroseconds:"		"\n\t"
#if F_CPU < 24000000
		"nop"					"\n\t"
#endif
		"subs   %0, #1"				"\n\t"
		"bne    L_%=_delayMicroseconds"		"\n"
		: "+r" (n) :
	);
}