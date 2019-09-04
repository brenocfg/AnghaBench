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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ERROR_ALREADY_EXISTS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/ * GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ReadVolumeSector (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _stprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,char*,...) ; 

BOOL BackupBootSector(LPCTSTR lpszVolumeName)
{
    HANDLE    hBackupFile;
    TCHAR    szFileName[MAX_PATH];
    ULONG    Count;
    BYTE    BootSectorBuffer[512];
    DWORD    dwNumberOfBytesWritten;
    BOOL    bRetVal;

    //
    // Find the next unused filename and open it
    //
    for (Count=0; ; Count++)
    {
        //
        // Generate the next filename
        //
        _stprintf(szFileName, _T("%s\\bootsect.%03ld"), lpszVolumeName, Count);

        //
        // Try to create a new file, fail if exists
        //
        hBackupFile = CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_NEW, /*FILE_ATTRIBUTE_SYSTEM*/0, NULL);

        //
        // Check to see if it worked
        //
        if (hBackupFile != INVALID_HANDLE_VALUE)
        {
            break;
        }

        //
        // Nope, didn't work
        // Check to see if it already existed
        //
        if (!(GetLastError() != ERROR_ALREADY_EXISTS))
        {
            _tprintf(_T("%s:%d: "), __FILE__, __LINE__);
            _tprintf(_T("Boot sector backup failed. Error code %ld.\n"), GetLastError());
            return FALSE;
        }
    }

    //
    // Try to read the boot sector
    //
    if (!ReadVolumeSector(0, BootSectorBuffer))
    {
        CloseHandle(hBackupFile);
        return FALSE;
    }

    //
    // Try to write the boot sector data to the file
    //
    bRetVal = WriteFile(hBackupFile, BootSectorBuffer, 512, &dwNumberOfBytesWritten, NULL);
    if (!bRetVal || (dwNumberOfBytesWritten != 512))
    {
        CloseHandle(hBackupFile);
        _tprintf(_T("%s:%d: "), __FILE__, __LINE__);
        _tprintf(_T("WriteFile() failed. Error code %ld.\n"), GetLastError());
        return FALSE;
    }

    _tprintf(_T("Boot sector backed up to file: %s\n"), szFileName);

    CloseHandle(hBackupFile);

    return TRUE;
}