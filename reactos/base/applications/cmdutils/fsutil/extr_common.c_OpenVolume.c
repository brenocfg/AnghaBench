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
typedef  scalar_t__ UINT ;
typedef  int TCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ CreateFile (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ DRIVE_REMOTE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetDriveType (int const*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetVolumeInformation (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PrintErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _stprintf (int*,int /*<<< orphan*/ ,int const*) ; 
 scalar_t__ _tcscmp (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

HANDLE OpenVolume(const TCHAR * Volume,
                  BOOLEAN AllowRemote,
                  BOOLEAN NtfsOnly)
{
    UINT Type;
    HANDLE hVolume;
    TCHAR VolumeID[PATH_MAX];

    /* Get volume type */
    if (!AllowRemote && Volume[1] == L':')
    {
        Type = GetDriveType(Volume);
        if (Type == DRIVE_REMOTE)
        {
            _ftprintf(stderr, _T("FSUTIL needs a local device\n"));
            return INVALID_HANDLE_VALUE;
        }
    }

    /* Get filesystem type */
    if (NtfsOnly)
    {
        TCHAR FileSystem[MAX_PATH + 1];

        _stprintf(VolumeID, _T("\\\\.\\%s\\"), Volume);
        if (!GetVolumeInformation(VolumeID, NULL,  0, NULL, NULL, NULL, FileSystem, MAX_PATH + 1))
        {
            PrintErrorMessage(GetLastError());
            return INVALID_HANDLE_VALUE;
        }

        if (_tcscmp(FileSystem, _T("NTFS")) != 0)
        {
            _ftprintf(stderr, _T("FSUTIL needs a NTFS device\n"));
            return INVALID_HANDLE_VALUE;
        }
    }

    /* Create full name */
    _stprintf(VolumeID, _T("\\\\.\\%s"), Volume);

    /* Open the volume */
    hVolume = CreateFile(VolumeID, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                         NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hVolume == INVALID_HANDLE_VALUE)
    {
        PrintErrorMessage(GetLastError());
        return INVALID_HANDLE_VALUE;
    }

    return hVolume;
}