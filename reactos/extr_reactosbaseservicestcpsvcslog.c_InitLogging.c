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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

BOOL
InitLogging()
{
#ifdef DEBUG
    BOOL bRet = FALSE;

    if (!GetEnvironmentVariableW(L"SystemDrive", szLogFileName, ARRAYSIZE(szLogFileName)))
    {
        StringCchCopyW(szLogFileName, ARRAYSIZE(szLogFileName), L"C:");
    }
    StringCchCatW(szLogFileName, ARRAYSIZE(szLogFileName), L"\\tcpsvcs_log.log");

    ZeroMemory(&olWrite, sizeof(OVERLAPPED));
    olWrite.Offset = 0xFFFFFFFF;
    olWrite.OffsetHigh = 0xFFFFFFFF;
    olWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (olWrite.hEvent)
    {
        DeleteFileW(szLogFileName);

        if (OpenLogFile())
        {
            WCHAR wcBom = 0xFEFF;
            DWORD bytesWritten;

            bRet = WriteFile(hLogFile,
                             &wcBom,
                             sizeof(WCHAR),
                             &bytesWritten,
                             &olWrite);
            if (!bRet)
            {
                if (GetLastError() != ERROR_IO_PENDING)
                {
                    LogToEventLog(L"Failed to write to log file",
                                  GetLastError(),
                                  0,
                                  LOG_EVENTLOG | LOG_ERROR);
                }
                else
                {
                    bRet = TRUE;
                }
            }
        }
    }

    return bRet;
#else
    return TRUE;
#endif
}