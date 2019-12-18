#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  overlap ;
struct TYPE_5__ {int /*<<< orphan*/  hEvent; } ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  TYPE_1__ OVERLAPPED ;
typedef  int /*<<< orphan*/  MMRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ERROR_IO_PENDING ; 
 int /*<<< orphan*/  ErrorToMmResult (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetOverlappedResult (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOMEM ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ WAIT_IO_COMPLETION ; 
 scalar_t__ WaitForSingleObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

MMRESULT
GetDeviceData(
    HANDLE device_handle,
    DWORD ioctl,
    PBYTE output_buffer,
    DWORD buffer_size)
{
    OVERLAPPED overlap;
    DWORD bytes_returned;
    BOOL success;
    DWORD transfer;

    DPRINT("GetDeviceData\n");

    memset(&overlap, 0, sizeof(overlap));

    overlap.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    if ( ! overlap.hEvent )
        return MMSYSERR_NOMEM;

    success = DeviceIoControl(device_handle,
                              ioctl,
                              NULL,
                              0,
                              output_buffer,
                              buffer_size,
                              &bytes_returned,
                              &overlap);

    if ( ! success )
    {
        if ( GetLastError() == ERROR_IO_PENDING )
        {
            if ( ! GetOverlappedResult(device_handle, &overlap, &transfer, TRUE) )
            {
                CloseHandle(overlap.hEvent);
                return ErrorToMmResult(GetLastError());
            }
        }
        else
        {
            CloseHandle(overlap.hEvent);
            return ErrorToMmResult(GetLastError());
        }
    }

    while ( TRUE )
    {
        SetEvent(overlap.hEvent);

        if ( WaitForSingleObjectEx(overlap.hEvent, 0, TRUE) != WAIT_IO_COMPLETION )
        {
            break;
        }
    }

    CloseHandle(overlap.hEvent);

    return MMSYSERR_NOERROR;
}