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
typedef  int ULONGLONG ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int _wcstoui64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_sr98_em4100_blocks (int*,int) ; 
 int /*<<< orphan*/  kuhl_m_sr98_sendBlocks (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_sr98_em4100(int argc, wchar_t * argv[])
{
	PCWCHAR szNumber;
	ULONGLONG Number;
	ULONG blocks[3];

	kprintf(L"\nEM4100 encoder\n\n");
	if(kull_m_string_args_byName(argc, argv, L"id", &szNumber, NULL))
	{
		Number = _wcstoui64(szNumber, NULL, 0);
		if((Number < 0x10000000000))
		{
			kprintf(L" * Tag ID      : %I64u (0x%I64x)\n", Number, Number);
			kuhl_m_sr98_em4100_blocks(blocks, Number);
			kprintf(L" * EM4100      : 0x%08x%08x\n", blocks[1], blocks[2]);
			kuhl_m_sr98_sendBlocks(blocks, ARRAYSIZE(blocks));
		}
		else PRINT_ERROR(L"Tag Id (/id) must be in the [0;255] range - it was %I64u (0x%I64x)", Number, Number);
	}
	else PRINT_ERROR(L"Tag Id (/id) is needed\n");
	return STATUS_SUCCESS;
}