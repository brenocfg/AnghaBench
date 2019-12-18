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
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/ * LPCBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 char** PRINTF_TYPES ; 
 int /*<<< orphan*/  dprintf (char const*,...) ; 

void kull_m_string_dprintf_hex(LPCVOID lpData, DWORD cbData, DWORD flags)
{
	DWORD i, sep = flags >> 16;
	const char * pType = PRINTF_TYPES[flags & 0x0000000f];
	for(i = 0; i < cbData; i++)
	{
		dprintf(pType, ((LPCBYTE) lpData)[i]);
		if(sep && !((i+1) % sep))
			dprintf("\n");
	}
}