#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ InputReportByteLength; } ;
struct TYPE_5__ {scalar_t__ hBusy; int /*<<< orphan*/  id; TYPE_1__ hidCaps; } ;
typedef  TYPE_2__* PBUSYLIGHT_DEVICE ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/  LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__,...) ; 
 scalar_t__ ReadFile (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 

BOOL kull_m_busylight_device_read_raw(PBUSYLIGHT_DEVICE device, LPVOID *data, DWORD *size)
{
	BOOL status = FALSE;
	DWORD toRead;
	if(device && device->hBusy && (device->hBusy != INVALID_HANDLE_VALUE))
	{
		toRead = device->hidCaps.InputReportByteLength;
		if(*data = LocalAlloc(LPTR, toRead))
		{
			status = ReadFile(device->hBusy, *data, toRead, size, NULL);
			if(!status || (status && (*size != toRead)))
			{
				if(!status)
					PRINT_ERROR(L"[device %u] ReadFile (0x%08x)\n", device->id, GetLastError());
				else
					PRINT_ERROR(L"[device %u] %u byte(s) readed, %u wanted\n", *size, toRead);
				*data = LocalFree(*data);
				*size = 0;
			}
		}
	}
	else PRINT_ERROR(L"[device %u] Invalid Device/Busy Handle\n", device->id);
	return status;
}