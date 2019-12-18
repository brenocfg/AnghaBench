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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int USHORT ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_sr98_noralsy_blocks (int*,int,int) ; 
 int /*<<< orphan*/  kuhl_m_sr98_sendBlocks (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,char*) ; 
 int wcstoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_sr98_noralsy(int argc, wchar_t * argv[])
{
	PCWCHAR szNumber;
	ULONG Number = 0, blocks[4];
	USHORT Year, i;// = 1999;

	if(kull_m_string_args_byName(argc, argv, L"year", &szNumber, L"1999"))
	{
		Number = wcstoul(szNumber, NULL, 0);
		if(Number <= 0xffff)
		{
			Year = (USHORT) Number;
			kprintf(L" * Year        : %hu (0x%04x)\n", Year, Year);
			if(kull_m_string_args_byName(argc, argv, L"id", &szNumber, NULL))
			{
				Number = wcstoul(szNumber, NULL, 0);
				if(Number < 10000000)
				{
					kprintf(L" * Tag ID      : %u (0x%08x)\n", Number, Number);
					kuhl_m_sr98_noralsy_blocks(blocks, Number, Year);
					kprintf(L" * RAW         : ");
					for(i = 1; i < 4; i++)
						kprintf(L"%08x", blocks[i]);
					kprintf(L"\n");
					kuhl_m_sr98_sendBlocks(blocks, ARRAYSIZE(blocks));
				}
				else PRINT_ERROR(L"Tag Id (/id) must be in the [0;9999999] range - it was %u (0x%08x)\n", Number, Number);
			}
			else PRINT_ERROR(L"Tag Id (/id) is needed\n");
		}
		else PRINT_ERROR(L"Year (/year) must be in the [0;0xffff] range - it was %u (0x%08x)\n", Number, Number);
	}
	return STATUS_SUCCESS;
}