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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hPortHandle ; 

BOOL Rs232WriteByteWin32(BYTE DataByte)
{
    DWORD    BytesWritten = 0;
    BOOL    Success;
    DWORD    ErrorCode;

    Success = WriteFile(hPortHandle, &DataByte, 1, &BytesWritten, NULL);

    if (!Success || BytesWritten != 1)
    {
        ErrorCode = GetLastError();

        _tprintf(TEXT("WriteFile() failed. GetLastError() = %lu.\n"), ErrorCode);

        return FALSE;
    }

    return TRUE;
}