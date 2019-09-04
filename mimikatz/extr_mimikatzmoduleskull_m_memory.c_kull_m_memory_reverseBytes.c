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
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  void** PBYTE ;
typedef  void* BYTE ;

/* Variables and functions */

void kull_m_memory_reverseBytes(PVOID start, SIZE_T size)
{
	PBYTE lo = (PBYTE) start, hi = lo + size - 1;
	BYTE swap;
	while (lo < hi)
	{
		swap = *lo;
		*lo++ = *hi;
		*hi-- = swap;
	}
}