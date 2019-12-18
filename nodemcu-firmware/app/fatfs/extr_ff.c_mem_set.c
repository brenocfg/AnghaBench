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
typedef  scalar_t__ UINT ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */

__attribute__((used)) static void mem_set (void* dst, int val, UINT cnt)
{
	BYTE *d = (BYTE*)dst;

	do {
		*d++ = (BYTE)val;
	} while (--cnt);
}