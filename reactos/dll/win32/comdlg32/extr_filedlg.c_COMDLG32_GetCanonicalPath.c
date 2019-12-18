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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PCIDLIST_ABSOLUTE ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  COMDLG32_GetDisplayNameOf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathAddBackslashW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PathCanonicalizeW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PathGetDriveNumberW (int /*<<< orphan*/ *) ; 
 scalar_t__ PathIsRelativeW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void COMDLG32_GetCanonicalPath(PCIDLIST_ABSOLUTE pidlAbsCurrent,
                               LPWSTR lpstrFile, LPWSTR lpstrPathAndFile)
{
  WCHAR lpstrTemp[MAX_PATH];

  /* Get the current directory name */
  if (!COMDLG32_GetDisplayNameOf(pidlAbsCurrent, lpstrPathAndFile))
  {
    /* last fallback */
    GetCurrentDirectoryW(MAX_PATH, lpstrPathAndFile);
  }
  PathAddBackslashW(lpstrPathAndFile);

  TRACE("current directory=%s, file=%s\n", debugstr_w(lpstrPathAndFile), debugstr_w(lpstrFile));

  /* if the user specified a fully qualified path use it */
  if(PathIsRelativeW(lpstrFile))
  {
    lstrcatW(lpstrPathAndFile, lpstrFile);
  }
  else
  {
    /* does the path have a drive letter? */
    if (PathGetDriveNumberW(lpstrFile) == -1)
      lstrcpyW(lpstrPathAndFile+2, lpstrFile);
    else
      lstrcpyW(lpstrPathAndFile, lpstrFile);
  }

  /* resolve "." and ".." */
  PathCanonicalizeW(lpstrTemp, lpstrPathAndFile );
  lstrcpyW(lpstrPathAndFile, lpstrTemp);
  TRACE("canon=%s\n", debugstr_w(lpstrPathAndFile));
}