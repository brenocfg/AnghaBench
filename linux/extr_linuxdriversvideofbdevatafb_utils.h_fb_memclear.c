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

__attribute__((used)) static inline void *fb_memclear(void *s, size_t count)
{
	if (!count)
		return 0;

	if (count < 16) {
		asm volatile ("\n"
			"	lsr.l	#1,%1 ; jcc 1f ; clr.b (%0)+\n"
			"1:	lsr.l	#1,%1 ; jcc 1f ; clr.w (%0)+\n"
			"1:	lsr.l	#1,%1 ; jcc 1f ; clr.l (%0)+\n"
			"1:	lsr.l	#1,%1 ; jcc 1f ; clr.l (%0)+ ; clr.l (%0)+\n"
			"1:"
			: "=a" (s), "=d" (count)
			: "0" (s), "1" (count));
	} else {
		long tmp;
		asm volatile ("\n"
			"	move.l	%1,%2\n"
			"	lsr.l	#1,%2 ; jcc 1f ; clr.b (%0)+ ; subq.w #1,%1\n"
			"	lsr.l	#1,%2 ; jcs 2f\n"  /* %0 increased=>bit 2 switched*/
			"	clr.w	(%0)+  ; subq.w  #2,%1 ; jra 2f\n"
			"1:	lsr.l	#1,%2 ; jcc 2f\n"
			"	clr.w	(%0)+  ; subq.w  #2,%1\n"
			"2:	move.w	%1,%2; lsr.l #2,%1 ; jeq 6f\n"
			"	lsr.l	#1,%1 ; jcc 3f ; clr.l (%0)+\n"
			"3:	lsr.l	#1,%1 ; jcc 4f ; clr.l (%0)+ ; clr.l (%0)+\n"
			"4:	subq.l	#1,%1 ; jcs 6f\n"
			"5:	clr.l	(%0)+; clr.l (%0)+ ; clr.l (%0)+ ; clr.l (%0)+\n"
			"	dbra	%1,5b ; clr.w %1; subq.l #1,%1; jcc 5b\n"
			"6:	move.w	%2,%1; btst #1,%1 ; jeq 7f ; clr.w (%0)+\n"
			"7:	btst	#0,%1 ; jeq 8f ; clr.b (%0)+\n"
			"8:"
			: "=a" (s), "=d" (count), "=d" (tmp)
			: "0" (s), "1" (count));
	}

	return 0;
}