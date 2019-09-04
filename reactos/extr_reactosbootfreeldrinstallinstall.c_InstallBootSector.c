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
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ReadVolumeSector (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteVolumeSector (int,scalar_t__) ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fat32_data ; 
 scalar_t__ fat_data ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 

BOOL InstallBootSector(LPCTSTR lpszVolumeType)
{
    BYTE    BootSectorBuffer[512];

    //
    // Read in the old boot sector
    //
    if (!ReadVolumeSector(0, BootSectorBuffer))
    {
        return FALSE;
    }

    if (_tcsicmp(lpszVolumeType, _T("fat")) == 0)
    {
        //
        // Update the BPB in the new boot sector
        //
        memcpy((fat_data+3), (BootSectorBuffer+3), 59 /*fat BPB length*/);

        //
        // Write out new boot sector
        //
        if (!WriteVolumeSector(0, fat_data))
        {
            return FALSE;
        }
    }
    else if (_tcsicmp(lpszVolumeType, _T("fat32")) == 0)
    {
        //
        // Update the BPB in the new boot sector
        //
        memcpy((fat32_data+3), (BootSectorBuffer+3), 87 /*fat32 BPB length*/);

        //
        // Write out new boot sector
        //
        if (!WriteVolumeSector(0, fat32_data))
        {
            return FALSE;
        }

        //
        // Write out new extra sector
        //
        if (!WriteVolumeSector(14, (fat32_data+512)))
        {
            return FALSE;
        }
    }
    else
    {
        _tprintf(_T("%s:%d: "), __FILE__, __LINE__);
        _tprintf(_T("File system type %s unknown.\n"), lpszVolumeType);
        return FALSE;
    }

    _tprintf(_T("%s boot sector installed.\n"), lpszVolumeType);

    return TRUE;
}