#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WIN32_FIND_DATAW ;
struct TYPE_7__ {scalar_t__ lpszName; scalar_t__ bIsDirectory; int /*<<< orphan*/  nSize; int /*<<< orphan*/  tmLastModified; } ;
struct TYPE_6__ {int /*<<< orphan*/  cFileName; int /*<<< orphan*/  dwFileAttributes; int /*<<< orphan*/  nFileSizeLow; scalar_t__ nFileSizeHigh; int /*<<< orphan*/  ftLastAccessTime; int /*<<< orphan*/  ftCreationTime; int /*<<< orphan*/  ftLastWriteTime; } ;
typedef  TYPE_1__* LPWIN32_FIND_DATAW ;
typedef  TYPE_2__* LPFILEPROPERTIESW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  SystemTimeToFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL FTP_ConvertFileProp(LPFILEPROPERTIESW lpafp, LPWIN32_FIND_DATAW lpFindFileData)
{
    BOOL bSuccess = FALSE;

    ZeroMemory(lpFindFileData, sizeof(WIN32_FIND_DATAW));

    if (lpafp)
    {
        SystemTimeToFileTime( &lpafp->tmLastModified, &lpFindFileData->ftLastAccessTime );
	lpFindFileData->ftLastWriteTime = lpFindFileData->ftLastAccessTime;
	lpFindFileData->ftCreationTime = lpFindFileData->ftLastAccessTime;
	
        /* Not all fields are filled in */
        lpFindFileData->nFileSizeHigh = 0; /* We do not handle files bigger than 0xFFFFFFFF bytes yet :-) */
        lpFindFileData->nFileSizeLow = lpafp->nSize;

	if (lpafp->bIsDirectory)
	    lpFindFileData->dwFileAttributes |= FILE_ATTRIBUTE_DIRECTORY;

        if (lpafp->lpszName)
            lstrcpynW(lpFindFileData->cFileName, lpafp->lpszName, MAX_PATH);

	bSuccess = TRUE;
    }

    return bSuccess;
}