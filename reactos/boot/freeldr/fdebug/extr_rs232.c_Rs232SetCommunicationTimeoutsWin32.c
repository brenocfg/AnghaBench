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
struct TYPE_4__ {void* WriteTotalTimeoutMultiplier; void* WriteTotalTimeoutConstant; void* ReadTotalTimeoutMultiplier; void* ReadTotalTimeoutConstant; void* ReadIntervalTimeout; } ;
typedef  void* DWORD ;
typedef  TYPE_1__ COMMTIMEOUTS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCommTimeouts (int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* GetLastError () ; 
 int /*<<< orphan*/  SetCommTimeouts (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  hPortHandle ; 

BOOL Rs232SetCommunicationTimeoutsWin32(DWORD ReadIntervalTimeout, DWORD ReadTotalTimeoutMultiplier, DWORD ReadTotalTimeoutConstant, DWORD WriteTotalTimeoutMultiplier, DWORD WriteTotalTimeoutConstant)
{
    COMMTIMEOUTS    ct;
    DWORD            ErrorCode;

    if (!GetCommTimeouts(hPortHandle, &ct))
    {
        ErrorCode = GetLastError();

        _tprintf(TEXT("GetCommTimeouts() failed. GetLastError() = %lu.\n"), ErrorCode);

        return FALSE;
    }

    ct.ReadIntervalTimeout = ReadIntervalTimeout;
    ct.ReadTotalTimeoutConstant = ReadTotalTimeoutConstant;
    ct.ReadTotalTimeoutMultiplier = ReadTotalTimeoutMultiplier;
    ct.WriteTotalTimeoutConstant = WriteTotalTimeoutConstant;
    ct.WriteTotalTimeoutMultiplier = WriteTotalTimeoutMultiplier;

    if (!SetCommTimeouts(hPortHandle, &ct))
    {
        ErrorCode = GetLastError();

        _tprintf(TEXT("SetCommTimeouts() failed. GetLastError() = %lu.\n"), ErrorCode);

        return FALSE;
    }

    return TRUE;
}