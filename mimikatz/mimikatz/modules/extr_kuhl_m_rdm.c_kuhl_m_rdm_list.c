#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  VersionNumber; int /*<<< orphan*/  ProductID; int /*<<< orphan*/  VendorID; } ;
struct TYPE_6__ {TYPE_1__ hidAttributes; int /*<<< orphan*/  DevicePath; int /*<<< orphan*/  id; struct TYPE_6__* next; } ;
typedef  TYPE_2__* PRDM_DEVICE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdm_devices_free (TYPE_2__*) ; 
 scalar_t__ rdm_devices_get (TYPE_2__**,int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_rdm_list(int argc, wchar_t * argv[])
{
	PRDM_DEVICE devices, cur;
	ULONG count;
	if(rdm_devices_get(&devices, &count))
	{
		for(cur = devices; cur; cur = cur->next)
			kprintf(L"\n[%3u] %s\n  Vendor: 0x%04x, Product: 0x%04x, Version: 0x%04x\n", cur->id, cur->DevicePath, cur->hidAttributes.VendorID, cur->hidAttributes.ProductID, cur->hidAttributes.VersionNumber);
		rdm_devices_free(devices);
	}
	else PRINT_ERROR(L"No device found\n");
	return STATUS_SUCCESS;
}