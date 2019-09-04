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
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int VMX_MAX ; 
 int /*<<< orphan*/  printf (char*,int,unsigned long,int,unsigned long) ; 

int validate_vmx(unsigned long vmx[][2], unsigned long *load)
{
	int i;

	for (i = 0; i < VMX_MAX; i++) {
		#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		if ((vmx[i][0] != load[64 + 2 * i]) ||
				(vmx[i][1] != load[65 + 2 * i])) {
			printf("vmx[%d][0]: %lx load[%d] %lx\n",
					i, vmx[i][0], 64 + 2 * i,
					load[64 + 2 * i]);
			printf("vmx[%d][1]: %lx load[%d] %lx\n",
					i, vmx[i][1], 65 + 2 * i,
					load[65 + 2 * i]);
			return TEST_FAIL;
		}
		#else  /*
			* In LE each value pair is stored in an
			* alternate manner.
			*/
		if ((vmx[i][0] != load[65 + 2 * i]) ||
				(vmx[i][1] != load[64 + 2 * i])) {
			printf("vmx[%d][0]: %lx load[%d] %lx\n",
					i, vmx[i][0], 65 + 2 * i,
					load[65 + 2 * i]);
			printf("vmx[%d][1]: %lx load[%d] %lx\n",
					i, vmx[i][1], 64 + 2 * i,
					load[64 + 2 * i]);
			return TEST_FAIL;
		}
		#endif
	}
	return TEST_PASS;
}