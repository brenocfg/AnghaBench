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
typedef  int /*<<< orphan*/  dcb ;
struct TYPE_5__ {int DCBlength; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DCB ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BuildCommDCB (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  MAXDWORD ; 
 int /*<<< orphan*/  Rs232SetCommunicationTimeoutsWin32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCommState (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hPortHandle ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

BOOL Rs232ConfigurePortWin32(TCHAR* DeviceControlString)
{
    DCB        dcb;
    DWORD    ErrorCode;

    /*if (!GetCommState(hPortHandle, &dcb))
    {
        ErrorCode = GetLastError();

        _tprintf(TEXT("GetCommState() failed. GetLastError() = %lu.\n"), ErrorCode);

        return FALSE;
    }

    dcb.BaudRate = BaudRate;
    dcb.ByteSize = DataBits;
    dcb.Parity = Parity;
    dcb.StopBits = StopBits;
    dcb.fBinary = TRUE;
    dcb.fDsrSensitivity = FALSE;
    dcb.fParity = (Parity == NOPARITY) ? FALSE : TRUE;
    dcb.fOutX = FALSE;
    dcb.fInX = FALSE;
    dcb.fNull = FALSE;
    dcb.fAbortOnError = TRUE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl = DTR_CONTROL_DISABLE;
    dcb.fDsrSensitivity = FALSE;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxCtsFlow = FALSE;*/


    memset(&dcb, 0, sizeof(DCB));
    dcb.DCBlength = sizeof(dcb);
    if (!BuildCommDCB(DeviceControlString, &dcb))
    {
        ErrorCode = GetLastError();

        _tprintf(TEXT("BuildCommDCB() failed. GetLastError() = %lu.\n"), ErrorCode);

        return FALSE;
    }

    if (!SetCommState(hPortHandle, &dcb))
    {
        ErrorCode = GetLastError();

        _tprintf(TEXT("SetCommState() failed. GetLastError() = %lu.\n"), ErrorCode);

        return FALSE;
    }

    // Set the timeouts
    if (!Rs232SetCommunicationTimeoutsWin32(MAXDWORD, 0, 0, 0, 0))
    {
        return FALSE;
    }

    return TRUE;
}