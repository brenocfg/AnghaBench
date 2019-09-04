#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {scalar_t__ hEvent; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {int dwServiceNameOffset; scalar_t__ dwArgumentsOffset; scalar_t__ dwArgumentsCount; int /*<<< orphan*/  hServiceStatus; scalar_t__ dwControl; scalar_t__ dwSize; } ;
struct TYPE_11__ {scalar_t__ dwError; } ;
typedef  int /*<<< orphan*/  SERVICE_STATUS_HANDLE ;
typedef  TYPE_1__ SCM_REPLY_PACKET ;
typedef  int /*<<< orphan*/  SCM_CONTROL_PACKET ;
typedef  scalar_t__ PWSTR ;
typedef  TYPE_2__* PSCM_CONTROL_PACKET ;
typedef  scalar_t__ PBYTE ;
typedef  TYPE_3__ OVERLAPPED ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CancelIo (scalar_t__) ; 
 int /*<<< orphan*/  ControlServiceCriticalSection ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__) ; 
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SERVICE_REQUEST_TIMEOUT ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetOverlappedResult (scalar_t__,TYPE_3__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PipeTimeout ; 
 scalar_t__ ReadFile (scalar_t__,TYPE_1__*,int,scalar_t__*,TYPE_3__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ WriteFile (scalar_t__,TYPE_2__*,scalar_t__,scalar_t__*,TYPE_3__*) ; 
 int /*<<< orphan*/  wcscpy (scalar_t__,scalar_t__) ; 
 int wcslen (scalar_t__) ; 

DWORD
ScmControlService(HANDLE hControlPipe,
                  PWSTR pServiceName,
                  SERVICE_STATUS_HANDLE hServiceStatus,
                  DWORD dwControl)
{
    PSCM_CONTROL_PACKET ControlPacket;
    SCM_REPLY_PACKET ReplyPacket;

    DWORD dwWriteCount = 0;
    DWORD dwReadCount = 0;
    DWORD PacketSize;
    PWSTR Ptr;
    DWORD dwError = ERROR_SUCCESS;
    BOOL bResult;
    OVERLAPPED Overlapped = {0};

    DPRINT("ScmControlService() called\n");

    /* Acquire the service control critical section, to synchronize requests */
    EnterCriticalSection(&ControlServiceCriticalSection);

    /* Calculate the total length of the start command line */
    PacketSize = sizeof(SCM_CONTROL_PACKET);
    PacketSize += (DWORD)((wcslen(pServiceName) + 1) * sizeof(WCHAR));

    ControlPacket = HeapAlloc(GetProcessHeap(),
                              HEAP_ZERO_MEMORY,
                              PacketSize);
    if (ControlPacket == NULL)
    {
        LeaveCriticalSection(&ControlServiceCriticalSection);
        return ERROR_NOT_ENOUGH_MEMORY;
    }

    ControlPacket->dwSize = PacketSize;
    ControlPacket->dwControl = dwControl;
    ControlPacket->hServiceStatus = hServiceStatus;

    ControlPacket->dwServiceNameOffset = sizeof(SCM_CONTROL_PACKET);

    Ptr = (PWSTR)((PBYTE)ControlPacket + ControlPacket->dwServiceNameOffset);
    wcscpy(Ptr, pServiceName);

    ControlPacket->dwArgumentsCount = 0;
    ControlPacket->dwArgumentsOffset = 0;

    bResult = WriteFile(hControlPipe,
                        ControlPacket,
                        PacketSize,
                        &dwWriteCount,
                        &Overlapped);
    if (bResult == FALSE)
    {
        DPRINT("WriteFile() returned FALSE\n");

        dwError = GetLastError();
        if (dwError == ERROR_IO_PENDING)
        {
            DPRINT("dwError: ERROR_IO_PENDING\n");

            dwError = WaitForSingleObject(hControlPipe,
                                          PipeTimeout);
            DPRINT("WaitForSingleObject() returned %lu\n", dwError);

            if (dwError == WAIT_TIMEOUT)
            {
                bResult = CancelIo(hControlPipe);
                if (bResult == FALSE)
                {
                    DPRINT1("CancelIo() failed (Error: %lu)\n", GetLastError());
                }

                dwError = ERROR_SERVICE_REQUEST_TIMEOUT;
                goto Done;
            }
            else if (dwError == WAIT_OBJECT_0)
            {
                bResult = GetOverlappedResult(hControlPipe,
                                              &Overlapped,
                                              &dwWriteCount,
                                              TRUE);
                if (bResult == FALSE)
                {
                    dwError = GetLastError();
                    DPRINT1("GetOverlappedResult() failed (Error %lu)\n", dwError);

                    goto Done;
                }
            }
        }
        else
        {
            DPRINT1("WriteFile() failed (Error %lu)\n", dwError);
            goto Done;
        }
    }

    /* Read the reply */
    Overlapped.hEvent = (HANDLE) NULL;

    bResult = ReadFile(hControlPipe,
                       &ReplyPacket,
                       sizeof(SCM_REPLY_PACKET),
                       &dwReadCount,
                       &Overlapped);
    if (bResult == FALSE)
    {
        DPRINT("ReadFile() returned FALSE\n");

        dwError = GetLastError();
        if (dwError == ERROR_IO_PENDING)
        {
            DPRINT("dwError: ERROR_IO_PENDING\n");

            dwError = WaitForSingleObject(hControlPipe,
                                          PipeTimeout);
            DPRINT("WaitForSingleObject() returned %lu\n", dwError);

            if (dwError == WAIT_TIMEOUT)
            {
                bResult = CancelIo(hControlPipe);
                if (bResult == FALSE)
                {
                    DPRINT1("CancelIo() failed (Error: %lu)\n", GetLastError());
                }

                dwError = ERROR_SERVICE_REQUEST_TIMEOUT;
                goto Done;
            }
            else if (dwError == WAIT_OBJECT_0)
            {
                bResult = GetOverlappedResult(hControlPipe,
                                              &Overlapped,
                                              &dwReadCount,
                                              TRUE);
                if (bResult == FALSE)
                {
                    dwError = GetLastError();
                    DPRINT1("GetOverlappedResult() failed (Error %lu)\n", dwError);

                    goto Done;
                }
            }
        }
        else
        {
            DPRINT1("ReadFile() failed (Error %lu)\n", dwError);
            goto Done;
        }
    }

Done:
    /* Release the control packet */
    HeapFree(GetProcessHeap(),
             0,
             ControlPacket);

    if (dwReadCount == sizeof(SCM_REPLY_PACKET))
    {
        dwError = ReplyPacket.dwError;
    }

    LeaveCriticalSection(&ControlServiceCriticalSection);

    DPRINT("ScmControlService() done\n");

    return dwError;
}