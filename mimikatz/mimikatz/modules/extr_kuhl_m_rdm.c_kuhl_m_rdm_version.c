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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  hDevice; int /*<<< orphan*/  id; struct TYPE_4__* next; } ;
typedef  int /*<<< orphan*/  PSTR ;
typedef  TYPE_1__* PRDM_DEVICE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdm_devices_free (TYPE_1__*) ; 
 scalar_t__ rdm_devices_get (TYPE_1__**,int /*<<< orphan*/ *) ; 
 scalar_t__ rdm_get_version (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_rdm_version(int argc, wchar_t * argv[])
{
	PRDM_DEVICE devices, cur;
	ULONG count;
	PSTR version;

	if(rdm_devices_get(&devices, &count))
	{
		for(cur = devices; cur; cur = cur->next)
		{
			kprintf(L"[%3u] ", cur->id);
			if(rdm_get_version(cur->hDevice, &version))
			{
				kprintf(L"%S\n", version);
				LocalFree(version);
			}
		}
		rdm_devices_free(devices);
	}
	else PRINT_ERROR(L"No device found\n");
	return STATUS_SUCCESS;
}