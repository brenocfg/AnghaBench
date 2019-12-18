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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/  hEvent; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_IO_PENDING ; 
 int /*<<< orphan*/  EXCEPTION_INT_OVERFLOW ; 
 int /*<<< orphan*/  ExitProcess (int) ; 
 scalar_t__ FALSE ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FormatMessageW (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetOverlappedResult (int /*<<< orphan*/ ,TYPE_1__*,int*,scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int LOG_ERROR ; 
 int LOG_EVENTLOG ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogToEventLog (char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAXDWORD ; 
 int /*<<< orphan*/  RaiseException (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
#define  WAIT_OBJECT_0 128 
 int WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  hLogFile ; 
 TYPE_1__ olWrite ; 
 int wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VOID
LogToFile(LPCWSTR lpMsg,
          DWORD errNum,
          DWORD exitCode,
          UINT flags)
{
    LPWSTR lpFullMsg = NULL;
    SIZE_T msgLen;

    msgLen = wcslen(lpMsg) + 1;

    if (flags & LOG_ERROR)
    {
        LPWSTR lpSysMsg;
        DWORD eMsgLen;

        eMsgLen = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                                 NULL,
                                 errNum,
                                 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                 (LPWSTR)&lpSysMsg,
                                 0,
                                 NULL);

        msgLen = msgLen + eMsgLen + 40;

        lpFullMsg = HeapAlloc(GetProcessHeap(),
                              0,
                              msgLen * sizeof(TCHAR));
        if (lpFullMsg)
        {
            _snwprintf(lpFullMsg,
                       msgLen,
                       L"%s : %s\tErrNum = %lu ExitCode = %lu\r\n",
                       lpMsg,
                       lpSysMsg,
                       errNum,
                       exitCode);
        }

        LocalFree(lpSysMsg);

    }
    else
    {
        msgLen += 2;

        lpFullMsg = HeapAlloc(GetProcessHeap(),
                              0,
                              msgLen * sizeof(TCHAR));
        if (lpFullMsg)
        {
            _snwprintf(lpFullMsg,
                       msgLen,
                      L"%s\r\n",
                      lpMsg);
        }
    }

    /* Make sure the length in bytes doesn't overflow a DWORD */
    msgLen = wcslen(lpFullMsg);
    if (msgLen > (MAXDWORD / sizeof(WCHAR)))
    {
        RaiseException(EXCEPTION_INT_OVERFLOW, 0, 0, NULL);
    }

    if (lpFullMsg)
    {
        DWORD bytesWritten;
        DWORD dwRet;
        BOOL bRet;

        bRet = WriteFile(hLogFile,
                         lpFullMsg,
                         (DWORD)msgLen * sizeof(WCHAR),
                         &bytesWritten,
                         &olWrite);
        if (!bRet)
        {
            if (GetLastError() != ERROR_IO_PENDING)
            {
                bRet = FALSE;
            }
            else
            {
                // Write is pending
                dwRet = WaitForSingleObject(olWrite.hEvent, INFINITE);

                 switch (dwRet)
                 {
                    // event has been signaled
                    case WAIT_OBJECT_0:
                    {
                         bRet = GetOverlappedResult(hLogFile,
                                                    &olWrite,
                                                    &bytesWritten,
                                                    FALSE);
                         break;
                    }

                    default:
                         // An error has occurred in WaitForSingleObject.
                         // This usually indicates a problem with the
                         // OVERLAPPED structure's event handle.
                         bRet = FALSE;
                         break;
                 }
            }
        }

        if (!bRet || bytesWritten == 0)
        {
            LogToEventLog(L"Failed to write to log file",
                          GetLastError(),
                          0,
                          LOG_EVENTLOG | LOG_ERROR);
        }

        HeapFree(GetProcessHeap(),
                 0,
                 lpFullMsg);
    }

    if (exitCode > 0)
        ExitProcess(exitCode);
}