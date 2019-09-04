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

__attribute__((used)) static void sh_eth_soft_swap(char *src, int len)
{
#ifdef __LITTLE_ENDIAN
	u32 *p = (u32 *)src;
	u32 *maxp = p + DIV_ROUND_UP(len, sizeof(u32));

	for (; p < maxp; p++)
		*p = swab32(*p);
#endif
}