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
typedef  int ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  hDevice; struct TYPE_4__* next; } ;
typedef  TYPE_1__* PSR98_DEVICE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  sr98_beep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr98_devices_free (TYPE_1__*) ; 
 scalar_t__ sr98_devices_get (TYPE_1__**,int*) ; 
 int wcstoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_sr98_beep(int argc, wchar_t * argv[])
{
	PSR98_DEVICE devices, cur;
	ULONG count, duration = 9;
	if(argc)
		duration = wcstoul(argv[0], NULL, 0);
	if(sr98_devices_get(&devices, &count))
	{
		for(cur = devices; cur; cur = cur->next)
			sr98_beep(cur->hDevice, (BYTE) duration);
		sr98_devices_free(devices);
	}
	else PRINT_ERROR(L"No device found\n");
	return STATUS_SUCCESS;
}