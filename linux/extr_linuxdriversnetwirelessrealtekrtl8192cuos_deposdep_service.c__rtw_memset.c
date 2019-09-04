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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

void _rtw_memset(void *pbuf, int c, u32 sz)
{

#if defined (PLATFORM_LINUX)|| defined (PLATFORM_FREEBSD)

        memset(pbuf, c, sz);

#endif

#ifdef PLATFORM_WINDOWS
#if 0
	NdisZeroMemory(pbuf, sz);
	if (c != 0) memset(pbuf, c, sz);
#else
	NdisFillMemory(pbuf, sz, c);
#endif
#endif

}