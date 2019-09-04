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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int SetFilePointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hDiskVolume ; 

BOOL ReadVolumeSector(ULONG SectorNumber, PVOID SectorBuffer)
{
    DWORD    dwNumberOfBytesRead;
    DWORD    dwFilePosition;
    BOOL    bRetVal;

    //
    // FIXME: this doesn't seem to handle the situation
    // properly when SectorNumber is bigger than the
    // amount of sectors on the disk. Seems to me that
    // the call to SetFilePointer() should just give an
    // out of bounds error or something but it doesn't.
    //
    dwFilePosition = SetFilePointer(hDiskVolume, (SectorNumber * 512), NULL, FILE_BEGIN);
    if (dwFilePosition != (SectorNumber * 512))
    {
        _tprintf(_T("%s:%d: "), __FILE__, __LINE__);
        _tprintf(_T("SetFilePointer() failed. Error code %ld.\n"), GetLastError());
        return FALSE;
    }

    bRetVal = ReadFile(hDiskVolume, SectorBuffer, 512, &dwNumberOfBytesRead, NULL);
    if (!bRetVal || (dwNumberOfBytesRead != 512))
    {
        _tprintf(_T("%s:%d: "), __FILE__, __LINE__);
        _tprintf(_T("ReadFile() failed. Error code %ld.\n"), GetLastError());
        return FALSE;
    }

    return TRUE;
}