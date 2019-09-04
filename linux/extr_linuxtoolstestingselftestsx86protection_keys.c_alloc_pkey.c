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
 int /*<<< orphan*/  __rdpkru () ; 
 int /*<<< orphan*/  dprintf1 (char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dprintf4 (char*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  rdpkru () ; 
 int shadow_pkru ; 
 int sys_pkey_alloc (int /*<<< orphan*/ ,unsigned long) ; 

int alloc_pkey(void)
{
	int ret;
	unsigned long init_val = 0x0;

	dprintf1("alloc_pkey()::%d, pkru: 0x%x shadow: %x\n",
			__LINE__, __rdpkru(), shadow_pkru);
	ret = sys_pkey_alloc(0, init_val);
	/*
	 * pkey_alloc() sets PKRU, so we need to reflect it in
	 * shadow_pkru:
	 */
	dprintf4("alloc_pkey()::%d, ret: %d pkru: 0x%x shadow: 0x%x\n",
			__LINE__, ret, __rdpkru(), shadow_pkru);
	if (ret) {
		/* clear both the bits: */
		shadow_pkru &= ~(0x3      << (ret * 2));
		dprintf4("alloc_pkey()::%d, ret: %d pkru: 0x%x shadow: 0x%x\n",
				__LINE__, ret, __rdpkru(), shadow_pkru);
		/*
		 * move the new state in from init_val
		 * (remember, we cheated and init_val == pkru format)
		 */
		shadow_pkru |=  (init_val << (ret * 2));
	}
	dprintf4("alloc_pkey()::%d, ret: %d pkru: 0x%x shadow: 0x%x\n",
			__LINE__, ret, __rdpkru(), shadow_pkru);
	dprintf1("alloc_pkey()::%d errno: %d\n", __LINE__, errno);
	/* for shadow checking: */
	rdpkru();
	dprintf4("alloc_pkey()::%d, ret: %d pkru: 0x%x shadow: 0x%x\n",
			__LINE__, ret, __rdpkru(), shadow_pkru);
	return ret;
}