#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szDrive ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {scalar_t__ Count; TYPE_1__* Pagefile; int /*<<< orphan*/  szPagingFiles; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pszVolume; int /*<<< orphan*/  szDrive; int /*<<< orphan*/  bUsed; scalar_t__ NewMaxSize; scalar_t__ NewMinSize; scalar_t__ OldMaxSize; scalar_t__ OldMinSize; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_2__* PVIRTMEM ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ DRIVE_FIXED ; 
 scalar_t__ GetDriveType (int /*<<< orphan*/ *) ; 
 scalar_t__ GetLogicalDriveStrings (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetPageFileSizes (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetVolumeInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _tcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tcsncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * _tcsupr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ lstrlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VOID
ParseMemSettings(PVIRTMEM pVirtMem)
{
    TCHAR szDrives[1024];    // All drives
    LPTSTR DrivePtr = szDrives;
    TCHAR szDrive[3];        // Single drive
    TCHAR szVolume[MAX_PATH + 1];
    INT MinSize;
    INT MaxSize;
    INT DriveLen;
    INT PgCnt = 0;
    INT Len;

    DriveLen = GetLogicalDriveStrings(1023,
                                      szDrives);

    while (DriveLen != 0)
    {
        Len = lstrlen(DrivePtr) + 1;
        DriveLen -= Len;

        DrivePtr = _tcsupr(DrivePtr);

        /* Copy the 'X:' portion */
        lstrcpyn(szDrive, DrivePtr, sizeof(szDrive) / sizeof(TCHAR));

        if (GetDriveType(DrivePtr) == DRIVE_FIXED)
        {
            MinSize = -1;
            MaxSize = -1;

            /* Does drive match the one in the registry ? */
            if (!_tcsncmp(pVirtMem->szPagingFiles, szDrive, 2))
            {
                GetPageFileSizes(pVirtMem->szPagingFiles,
                                 &MinSize,
                                 &MaxSize);
            }

            pVirtMem->Pagefile[PgCnt].OldMinSize = MinSize;
            pVirtMem->Pagefile[PgCnt].OldMaxSize = MaxSize;
            pVirtMem->Pagefile[PgCnt].NewMinSize = MinSize;
            pVirtMem->Pagefile[PgCnt].NewMaxSize = MaxSize;
            pVirtMem->Pagefile[PgCnt].bUsed = TRUE;
            lstrcpy(pVirtMem->Pagefile[PgCnt].szDrive, szDrive);


            /* Get the volume label if there is one */
            if (GetVolumeInformation(DrivePtr,
                                     szVolume,
                                     MAX_PATH + 1,
                                     NULL,
                                     NULL,
                                     NULL,
                                     NULL,
                                     0))
            {
                pVirtMem->Pagefile[PgCnt].pszVolume = HeapAlloc(GetProcessHeap(),
                                                                0,
                                                                (_tcslen(szVolume) + 1) * sizeof(TCHAR));
                if (pVirtMem->Pagefile[PgCnt].pszVolume != NULL)
                    _tcscpy(pVirtMem->Pagefile[PgCnt].pszVolume, szVolume);
            }

            PgCnt++;
        }

        DrivePtr += Len;
    }

    pVirtMem->Count = PgCnt;
}