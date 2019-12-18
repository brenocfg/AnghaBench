#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  hDevice; } ;
typedef  TYPE_1__* PSR98_DEVICE ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int _byteswap_uint64 (int) ; 
 int _wcstoui64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_sr98_em4100_blocks (int*,int) ; 
 int /*<<< orphan*/  kuhl_m_sr98_sendBlocks (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sr98_devices_free (TYPE_1__*) ; 
 scalar_t__ sr98_devices_get (TYPE_1__**,int*) ; 
 scalar_t__ sr98_read_emid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_sr98_em4100(int argc, wchar_t * argv[])
{
	PCWCHAR szNumber;
	ULONGLONG Number = 0;
	ULONG blocks[3];
	PSR98_DEVICE devices;
	ULONG count;

	if(kull_m_string_args_byName(argc, argv, L"read", NULL, NULL))
	{
		kprintf(L"\nEM4100 reader\n\n");
		if(sr98_devices_get(&devices, &count))
		{
			if(count == 1)
			{
				if(sr98_read_emid(devices->hDevice, (PBYTE) &Number))
				{
					Number = _byteswap_uint64(Number);
					Number >>= 24;
					kprintf(L" * Tag ID      : %I64u (0x%I64x)\n", Number, Number);
				}
				else PRINT_ERROR(L"sr98_read_emid\n");
			}
			else PRINT_ERROR(L"Reader device is not unique (%u)\n", count);
			sr98_devices_free(devices);
		}
	}
	else if(kull_m_string_args_byName(argc, argv, L"id", &szNumber, NULL))
	{
		kprintf(L"\nEM4100 encoder\n\n");
		Number = _wcstoui64(szNumber, NULL, 0);
		if((Number < 0x10000000000))
		{
			kprintf(L" * Tag ID      : %I64u (0x%I64x)\n", Number, Number);
			kuhl_m_sr98_em4100_blocks(blocks, Number);
			kprintf(L" * EM4100      : 0x%08x%08x\n", blocks[1], blocks[2]);
			kuhl_m_sr98_sendBlocks(blocks, ARRAYSIZE(blocks));
		}
		else PRINT_ERROR(L"Tag Id (/id) must be in the [0;255] range - it was %I64u (0x%I64x)\n", Number, Number);
	}
	else PRINT_ERROR(L"Tag Id (/id) is needed, or /read\n");
	return STATUS_SUCCESS;
}