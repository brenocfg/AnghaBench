#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  lbselchstring; scalar_t__ hook; int /*<<< orphan*/  ofnW; int /*<<< orphan*/  hwnd; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ FD31_DATA ;

/* Variables and functions */
 int BUFFILE ; 
 int /*<<< orphan*/  BUFFILEALLOC ; 
 int /*<<< orphan*/  CD_LBSELCHANGE ; 
 scalar_t__ FD31_CallWindowProc (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FD31_ScanDir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FILE_bslash ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  MAKELONG (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 char* heap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  lst2 ; 
 int /*<<< orphan*/  lstrcatW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int lstrlenW (char*) ; 

__attribute__((used)) static LRESULT FD31_DirListDblClick( const FD31_DATA *lfs )
{
  LONG lRet;
  HWND hWnd = lfs->hwnd;
  LPWSTR pstr;
  WCHAR tmpstr[BUFFILE];

  /* get the raw string (with brackets) */
  lRet = SendDlgItemMessageW(hWnd, lst2, LB_GETCURSEL, 0, 0);
  if (lRet == LB_ERR) return TRUE;
  pstr = heap_alloc(BUFFILEALLOC);
  SendDlgItemMessageW(hWnd, lst2, LB_GETTEXT, lRet,
		     (LPARAM)pstr);
  lstrcpyW( tmpstr, pstr );
  heap_free(pstr);
  /* get the selected directory in tmpstr */
  if (tmpstr[0] == '[')
    {
      tmpstr[lstrlenW(tmpstr) - 1] = 0;
      lstrcpyW(tmpstr,tmpstr+1);
    }
  lstrcatW(tmpstr, FILE_bslash);

  FD31_ScanDir(lfs->ofnW, hWnd, tmpstr);
  /* notify the app */
  if (lfs->hook)
    {
      if (FD31_CallWindowProc(lfs, lfs->lbselchstring, lst2,
              MAKELONG(lRet,CD_LBSELCHANGE)))
        return TRUE;
    }
  return TRUE;
}