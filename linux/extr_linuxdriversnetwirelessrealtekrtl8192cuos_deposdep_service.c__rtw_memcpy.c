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

void _rtw_memcpy(void* dst, const void* src, u32 sz)
{

#if defined (PLATFORM_LINUX)|| defined (PLATFORM_FREEBSD)

	memcpy(dst, src, sz);

#endif	

#ifdef PLATFORM_WINDOWS

	NdisMoveMemory(dst, src, sz);

#endif

}