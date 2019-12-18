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
 int VEC_MAX ; 
 int VSX_MAX ; 
 int /*<<< orphan*/  printf (char*,int,unsigned long,int,unsigned long) ; 

int compare_vsx_vmx(unsigned long *store, unsigned long *load)
{
	int i;

	for (i = 0; i < VSX_MAX; i++) {
		if (store[1 + 2 * i] != load[1 + 2 * i]) {
			printf("store[%d]: %lx load[%d] %lx\n",
					1 + 2 * i, store[i],
					1 + 2 * i, load[i]);
			return TEST_FAIL;
		}
	}

	#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	for (i = 64; i < VEC_MAX; i++) {
		if (store[i] != load[i]) {
			printf("store[%d]: %lx load[%d] %lx\n",
					i, store[i], i, load[i]);
			return TEST_FAIL;
		}
	}
	#else	/* In LE each value pair is stored in an alternate manner */
	for (i = 64; i < VEC_MAX; i++) {
		if (!(i % 2) && (store[i] != load[i+1])) {
			printf("store[%d]: %lx load[%d] %lx\n",
					i, store[i], i+1, load[i+1]);
			return TEST_FAIL;
		}
		if ((i % 2) && (store[i] != load[i-1])) {
			printf("here store[%d]: %lx load[%d] %lx\n",
					i, store[i], i-1, load[i-1]);
			return TEST_FAIL;
		}
	}
	#endif
	return TEST_PASS;
}