#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int ULONG ;
typedef  size_t UCHAR ;
struct TYPE_7__ {int toProg; int data; } ;
struct TYPE_6__ {int /*<<< orphan*/  hDevice; } ;
typedef  TYPE_1__* PSR98_DEVICE ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ KUHL_M_SR98_RAW_BLOCK ;
typedef  int BOOLEAN ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_2__*) ; 
 int FALSE ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _byteswap_ulong (int) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_sr98_b0_descr (int) ; 
 int kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sr98_devices_free (TYPE_1__*) ; 
 scalar_t__ sr98_devices_get (TYPE_1__**,int*) ; 
 int /*<<< orphan*/  sr98_t5577_wipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr98_t5577_write_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* wcstoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_sr98_raw(int argc, wchar_t * argv[])
{
	KUHL_M_SR98_RAW_BLOCK blocks[8];
	PSR98_DEVICE devices;
	ULONG count;
	PCWCHAR szBlock;
	UCHAR i;
	BOOLEAN isBlock = FALSE, isWipe = kull_m_string_args_byName(argc, argv, L"wipe", NULL, NULL);
	
	if(isBlock |= (blocks[0].toProg = kull_m_string_args_byName(argc, argv, L"b0", &szBlock, NULL)))
	{
		blocks[0].data = wcstoul(szBlock, NULL, 0);
		kuhl_m_sr98_b0_descr(blocks[0].data);
	}
	if(isBlock |= (blocks[1].toProg = kull_m_string_args_byName(argc, argv, L"b1", &szBlock, NULL)))
		blocks[1].data = wcstoul(szBlock, NULL, 0);
	if(isBlock |= (blocks[2].toProg = kull_m_string_args_byName(argc, argv, L"b2", &szBlock, NULL)))
		blocks[2].data = wcstoul(szBlock, NULL, 0);
	if(isBlock |= (blocks[3].toProg = kull_m_string_args_byName(argc, argv, L"b3", &szBlock, NULL)))
		blocks[3].data = wcstoul(szBlock, NULL, 0);
	if(isBlock |= (blocks[4].toProg = kull_m_string_args_byName(argc, argv, L"b4", &szBlock, NULL)))
		blocks[4].data = wcstoul(szBlock, NULL, 0);
	if(isBlock |= (blocks[5].toProg = kull_m_string_args_byName(argc, argv, L"b5", &szBlock, NULL)))
		blocks[5].data = wcstoul(szBlock, NULL, 0);
	if(isBlock |= (blocks[6].toProg = kull_m_string_args_byName(argc, argv, L"b6", &szBlock, NULL)))
		blocks[6].data = wcstoul(szBlock, NULL, 0);
	if(isBlock |= (blocks[7].toProg = kull_m_string_args_byName(argc, argv, L"b7", &szBlock, NULL)))
	{
		blocks[7].data = wcstoul(szBlock, NULL, 0);
		if(blocks[0].toProg && (blocks[0].data & 0x10)) // check PWD
			kprintf(L"\n> blocks[0] indicates PWD, blocks[7] will be the password (0x%08x)\n", blocks[7].data);
	}

	if(isBlock || isWipe)
	{
		if(sr98_devices_get(&devices, &count))
		{
			if(count == 1)
			{
				if(isWipe)
				{
					kprintf(L"\n * Wipe T5577 tag...\n");
					sr98_t5577_wipe(devices->hDevice, TRUE);
				}
				if(isBlock)
				{
					kprintf(L"\n * Write operations...\n");
					for(i = 0; i < ARRAYSIZE(blocks); i++)
					{
						if(blocks[i].toProg)
						{
							kprintf(L"   [%hhu] 0x%08x\n", i, blocks[i].data);
							sr98_t5577_write_block(devices->hDevice, 0, i, _byteswap_ulong(blocks[i].data), FALSE, 0);
						}
					}
				}
			}
			else PRINT_ERROR(L"Reader device is not unique (%u)\n", count);
			sr98_devices_free(devices);
		}
	}
	else PRINT_ERROR(L"No operation\n");
	return STATUS_SUCCESS;
}