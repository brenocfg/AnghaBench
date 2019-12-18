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
 int XSTATE_PKRU_BIT ; 
 int /*<<< orphan*/  __cpuid (unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int pkru_xstate_offset(void)
{
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	int xstate_offset;
	int xstate_size;
	unsigned long XSTATE_CPUID = 0xd;
	int leaf;

	/* assume that XSTATE_PKRU is set in XCR0 */
	leaf = XSTATE_PKRU_BIT;
	{
		eax = XSTATE_CPUID;
		ecx = leaf;
		__cpuid(&eax, &ebx, &ecx, &edx);

		if (leaf == XSTATE_PKRU_BIT) {
			xstate_offset = ebx;
			xstate_size = eax;
		}
	}

	if (xstate_size == 0) {
		printf("could not find size/offset of PKRU in xsave state\n");
		return 0;
	}

	return xstate_offset;
}