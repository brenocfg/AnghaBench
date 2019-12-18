#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPDCB ;
typedef  int /*<<< orphan*/  LPCOMMTIMEOUTS ;
typedef  char* INT ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetCommState (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetCommTimeouts (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  IDS_ERROR_DEVICE_NOT_AVAILABLE ; 
 int /*<<< orphan*/  IDS_ERROR_ILLEGAL_DEVICE_NAME ; 
 int /*<<< orphan*/  IDS_ERROR_STATUS_GET_DEVICE ; 
 int /*<<< orphan*/  IDS_ERROR_STATUS_SET_DEVICE ; 
 int /*<<< orphan*/  IDS_ERROR_TIMEOUT_GET_DEVICE ; 
 int /*<<< orphan*/  IDS_ERROR_TIMEOUT_SET_DEVICE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PORTNAME_LEN ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ SetCommState (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SetCommTimeouts (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static BOOL
SerialPortQuery(INT nPortNum, LPDCB pDCB, LPCOMMTIMEOUTS pCommTimeouts, BOOL bWrite)
{
    BOOL Success;
    HANDLE hPort;
    WCHAR szPortName[MAX_PORTNAME_LEN];

    ASSERT(pDCB);
    ASSERT(pCommTimeouts);

    swprintf(szPortName, L"COM%d", nPortNum);
    hPort = CreateFileW(szPortName,
                        bWrite ? GENERIC_WRITE : GENERIC_READ,
                        0,     // exclusive
                        NULL,  // sec attr
                        OPEN_EXISTING,
                        0,     // no attributes
                        NULL); // no template

    if (hPort == INVALID_HANDLE_VALUE)
    {
        DWORD dwLastError = GetLastError();
        if (dwLastError == ERROR_ACCESS_DENIED)
            ConResPrintf(StdErr, IDS_ERROR_DEVICE_NOT_AVAILABLE, szPortName);
        else
            ConResPrintf(StdErr, IDS_ERROR_ILLEGAL_DEVICE_NAME, szPortName, dwLastError);
        return FALSE;
    }

    Success = bWrite ? SetCommState(hPort, pDCB)
                     : GetCommState(hPort, pDCB);
    if (!Success)
    {
        ConResPrintf(StdErr,
                     bWrite ? IDS_ERROR_STATUS_SET_DEVICE : IDS_ERROR_STATUS_GET_DEVICE,
                     szPortName);
        goto Quit;
    }

    Success = bWrite ? SetCommTimeouts(hPort, pCommTimeouts)
                     : GetCommTimeouts(hPort, pCommTimeouts);
    if (!Success)
    {
        ConResPrintf(StdErr,
                     bWrite ? IDS_ERROR_TIMEOUT_SET_DEVICE : IDS_ERROR_TIMEOUT_GET_DEVICE,
                     szPortName);
        goto Quit;
    }

Quit:
    CloseHandle(hPort);
    return Success;
}