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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_TEXASR ; 
 int TEXASR_FS ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 unsigned long num_loops ; 
 scalar_t__ passed ; 

void texasr(void *in)
{
	unsigned long i;
	uint64_t result = 0;

	for (i = 0; i < num_loops; i++) {
		asm __volatile__(
			"tbegin.;"
			"beq    3f ;"
			"tabort. 0 ;"
			"tend.;"

			/* Abort handler */
			"3: ;"
			::: "memory");

                /* Check the TEXASR */
                result = mfspr(SPRN_TEXASR);
		if ((result & TEXASR_FS) == 0) {
			passed = 0;
			return;
		}
	}
	return;
}