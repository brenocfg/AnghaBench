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
typedef  int ULONG ;
typedef  size_t UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  hDevice; } ;
typedef  TYPE_1__* PSR98_DEVICE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _byteswap_ulong (int) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  sr98_devices_free (TYPE_1__*) ; 
 scalar_t__ sr98_devices_get (TYPE_1__**,int*) ; 
 int /*<<< orphan*/  sr98_t5577_write_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL kuhl_m_sr98_sendBlocks(ULONG *blocks, UCHAR nb)
{
	BOOL status = FALSE;
	PSR98_DEVICE devices;
	ULONG count;
	UCHAR i;
	if(sr98_devices_get(&devices, &count))
	{
		if(count == 1)
		{
			kprintf(L" * T5577 blocks:\n");
			for(i = 0; i < nb; i++)
				kprintf(L"   [%hhu] 0x%08x\n", i, blocks[i]);
			kprintf(L" * Write operations...\n");
			for(i = 0, status = TRUE; (i < nb) && status; i++)
				status &= sr98_t5577_write_block(devices->hDevice, 0, i, _byteswap_ulong(blocks[i]), FALSE, 0);
		}
		else PRINT_ERROR(L"Reader device is not unique (%u)\n", count);
		sr98_devices_free(devices);
	}
	return status;
}