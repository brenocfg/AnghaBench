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

bool ebb_is_supported(void)
{
#ifdef PPC_FEATURE2_EBB
	/* EBB requires at least POWER8 */
	return have_hwcap2(PPC_FEATURE2_EBB);
#else
	return false;
#endif
}