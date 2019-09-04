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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */

u_int mac_drv_check_space(void)
{
#ifdef	MB_OUTSIDE_SMC
#ifdef	COMMON_MB_POOL
	call_count++ ;
	if (call_count == 1) {
		return EXT_VIRT_MEM;
	}
	else {
		return EXT_VIRT_MEM_2;
	}
#else
	return EXT_VIRT_MEM;
#endif
#else
	return 0;
#endif
}