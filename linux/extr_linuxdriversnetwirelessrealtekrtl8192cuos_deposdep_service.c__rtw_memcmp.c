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

int	_rtw_memcmp(const void *dst, const void *src, u32 sz)
{

#if defined (PLATFORM_LINUX)|| defined (PLATFORM_FREEBSD)
//under Linux/GNU/GLibc, the return value of memcmp for two same mem. chunk is 0

	if (!(memcmp(dst, src, sz)))
		return _TRUE;
	else
		return _FALSE;
#endif


#ifdef PLATFORM_WINDOWS
//under Windows, the return value of NdisEqualMemory for two same mem. chunk is 1
	
	if (NdisEqualMemory (dst, src, sz))
		return _TRUE;
	else
		return _FALSE;

#endif	
	
	
	
}