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
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/ * LPCBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * WPRINTF_TYPES ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 

void kull_m_string_wprintf_hex(LPCVOID lpData, DWORD cbData, DWORD flags)
{
	DWORD i, sep = flags >> 16;
	PCWCHAR pType = WPRINTF_TYPES[flags & 0x0000000f];

	if((flags & 0x0000000f) == 2)
		kprintf(L"\nBYTE data[] = {\n\t");

	for(i = 0; i < cbData; i++)
	{
		kprintf(pType, ((LPCBYTE) lpData)[i]);
		if(sep && !((i+1) % sep))
		{
			kprintf(L"\n");
			if((flags & 0x0000000f) == 2)
				kprintf(L"\t");
		}
	}
	if((flags & 0x0000000f) == 2)
		kprintf(L"\n};\n");
}