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
typedef  int /*<<< orphan*/  OFSTRUCT ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HLOCAL ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GRPFILE_ModifyFileName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GRPFILE_ReadFileToBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GRPFILE_ScanGroup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ HFILE_ERROR ; 
 int /*<<< orphan*/  IDS_ERROR ; 
 int /*<<< orphan*/  IDS_GRPFILE_READ_ERROR_s ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_MessageBoxIDS_s (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATHNAME_LEN ; 
 int /*<<< orphan*/  MB_YESNO ; 
 int /*<<< orphan*/  OF_EXIST ; 
 scalar_t__ OpenFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

DWORD GRPFILE_ReadGroupFile(LPCWSTR lpszPath, BOOL bIsCommonGroup)
{
#if 0
  CHAR   szPath_gr[MAX_PATHNAME_LEN];
  BOOL   bFileNameModified = FALSE;
  OFSTRUCT dummy;
  HLOCAL hBuffer, hGroup;
  INT    size;

  /* if `.gr' file exists use that */
  GRPFILE_ModifyFileName(szPath_gr, lpszPath, MAX_PATHNAME_LEN, TRUE);
  if (OpenFile(szPath_gr, &dummy, OF_EXIST) != HFILE_ERROR)
    {
      lpszPath = szPath_gr;
      bFileNameModified = TRUE;
    }

  /* Read the whole file into a buffer */
  if (!GRPFILE_ReadFileToBuffer(lpszPath, &hBuffer, &size))
    {
      MAIN_MessageBoxIDS_s(IDS_GRPFILE_READ_ERROR_s, lpszPath, IDS_ERROR, MB_YESNO);
      return(0);
    }

  /* Interpret buffer */
  hGroup = GRPFILE_ScanGroup(LocalLock(hBuffer), size,
			     lpszPath, bFileNameModified);
  if (!hGroup)
    MAIN_MessageBoxIDS_s(IDS_GRPFILE_READ_ERROR_s, lpszPath, IDS_ERROR, MB_YESNO);

  LocalFree(hBuffer);

  return(hGroup);

#else
    return ERROR_SUCCESS;
#endif
}