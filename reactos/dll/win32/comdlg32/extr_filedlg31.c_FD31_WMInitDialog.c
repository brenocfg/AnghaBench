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
typedef  int /*<<< orphan*/  dir ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  char WCHAR ;
struct TYPE_7__ {int Flags; char* lpstrInitialDir; char* lpstrCustomFilter; int nFilterIndex; char* lpstrFile; scalar_t__ lpstrFilter; int /*<<< orphan*/  lpstrTitle; } ;
struct TYPE_6__ {int /*<<< orphan*/  lParam; scalar_t__ hook; TYPE_2__* ofnW; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__* PFD31_DATA ;
typedef  char* LPWSTR ;
typedef  TYPE_2__* LPOPENFILENAMEW ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int BUFFILE ; 
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CB_SETITEMDATA ; 
 int DDL_DRIVES ; 
 int DDL_EXCLUSIVE ; 
 scalar_t__ DRIVE_NO_ROOT_DIR ; 
 int /*<<< orphan*/  DlgDirListComboBoxW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FD31_CallWindowProc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* FD31_GetFileType (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  FD31_OFN_PROP ; 
 int /*<<< orphan*/  FD31_ScanDir (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int,char*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetDriveTypeA (char*) ; 
 int MAX_PATH ; 
 int OFN_HIDEREADONLY ; 
 int OFN_SHOWHELP ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SetPropA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  WM_INITDIALOG ; 
 int /*<<< orphan*/  chx1 ; 
 int /*<<< orphan*/  cmb1 ; 
 int /*<<< orphan*/  cmb2 ; 
 int debugstr_w (char*) ; 
 int /*<<< orphan*/  edt1 ; 
 int /*<<< orphan*/  lstrcpynW (char*,char*,int) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  pshHelp ; 
 scalar_t__ toupper (char) ; 

__attribute__((used)) static LONG FD31_WMInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
  int i, n;
  WCHAR tmpstr[BUFFILE];
  LPWSTR pstr, old_pstr;
  LPOPENFILENAMEW ofn;
  PFD31_DATA lfs = (PFD31_DATA) lParam;

  if (!lfs) return FALSE;
  SetPropA(hWnd, FD31_OFN_PROP, lfs);
  lfs->hwnd = hWnd;
  ofn = lfs->ofnW;

  TRACE("flags=%x initialdir=%s\n", ofn->Flags, debugstr_w(ofn->lpstrInitialDir));

  SetWindowTextW( hWnd, ofn->lpstrTitle );
  /* read custom filter information */
  if (ofn->lpstrCustomFilter)
    {
      pstr = ofn->lpstrCustomFilter;
      n = 0;
      TRACE("lpstrCustomFilter = %p\n", pstr);
      while(*pstr)
	{
	  old_pstr = pstr;
          i = SendDlgItemMessageW(hWnd, cmb1, CB_ADDSTRING, 0,
                                   (LPARAM)(ofn->lpstrCustomFilter) + n );
          n += lstrlenW(pstr) + 1;
	  pstr += lstrlenW(pstr) + 1;
	  TRACE("add str=%s associated to %s\n",
                debugstr_w(old_pstr), debugstr_w(pstr));
          SendDlgItemMessageW(hWnd, cmb1, CB_SETITEMDATA, i, (LPARAM)pstr);
          n += lstrlenW(pstr) + 1;
	  pstr += lstrlenW(pstr) + 1;
	}
    }
  /* read filter information */
  if (ofn->lpstrFilter) {
	pstr = (LPWSTR) ofn->lpstrFilter;
	n = 0;
	while(*pstr) {
	  old_pstr = pstr;
	  i = SendDlgItemMessageW(hWnd, cmb1, CB_ADDSTRING, 0,
				       (LPARAM)(ofn->lpstrFilter + n) );
	  n += lstrlenW(pstr) + 1;
	  pstr += lstrlenW(pstr) + 1;
	  TRACE("add str=%s associated to %s\n",
                debugstr_w(old_pstr), debugstr_w(pstr));
	  SendDlgItemMessageW(hWnd, cmb1, CB_SETITEMDATA, i, (LPARAM)pstr);
	  n += lstrlenW(pstr) + 1;
	  pstr += lstrlenW(pstr) + 1;
	}
  }
  /* set default filter */
  if (ofn->nFilterIndex == 0 && ofn->lpstrCustomFilter == NULL)
  	ofn->nFilterIndex = 1;
  SendDlgItemMessageW(hWnd, cmb1, CB_SETCURSEL, ofn->nFilterIndex - 1, 0);
  if (ofn->lpstrFile && ofn->lpstrFile[0])
  {
    TRACE( "SetText of edt1 to %s\n", debugstr_w(ofn->lpstrFile) );
    SetDlgItemTextW( hWnd, edt1, ofn->lpstrFile );
  }
  else
  {
    lstrcpynW(tmpstr, FD31_GetFileType(ofn->lpstrCustomFilter,
	     ofn->lpstrFilter, ofn->nFilterIndex - 1),BUFFILE);
    TRACE("nFilterIndex = %d, SetText of edt1 to %s\n",
  			ofn->nFilterIndex, debugstr_w(tmpstr));
    SetDlgItemTextW( hWnd, edt1, tmpstr );
  }
  /* get drive list */
  *tmpstr = 0;
  DlgDirListComboBoxW(hWnd, tmpstr, cmb2, 0, DDL_DRIVES | DDL_EXCLUSIVE);
  /* read initial directory */
  /* FIXME: Note that this is now very version-specific (See MSDN description of
   * the OPENFILENAME structure).  For example under 2000/XP any path in the
   * lpstrFile overrides the lpstrInitialDir, but not under 95/98/ME
   */
  if (ofn->lpstrInitialDir != NULL)
    {
      int len;
      lstrcpynW(tmpstr, ofn->lpstrInitialDir, 511);
      len = lstrlenW(tmpstr);
      if (len > 0 && tmpstr[len-1] != '\\'  && tmpstr[len-1] != ':') {
        tmpstr[len]='\\';
        tmpstr[len+1]='\0';
      }
    }
  else
    *tmpstr = 0;
  if (!FD31_ScanDir(ofn, hWnd, tmpstr)) {
    *tmpstr = 0;
    if (!FD31_ScanDir(ofn, hWnd, tmpstr))
      WARN("Couldn't read initial directory %s!\n", debugstr_w(tmpstr));
  }
  /* select current drive in combo 2, omit missing drives */
  {
      char dir[MAX_PATH];
      char str[4] = "a:\\";
      GetCurrentDirectoryA( sizeof(dir), dir );
      for(i = 0, n = -1; i < 26; i++)
      {
          str[0] = 'a' + i;
          if (GetDriveTypeA(str) > DRIVE_NO_ROOT_DIR) n++;
          if (toupper(str[0]) == toupper(dir[0])) break;
      }
  }
  SendDlgItemMessageW(hWnd, cmb2, CB_SETCURSEL, n, 0);
  if (!(ofn->Flags & OFN_SHOWHELP))
    ShowWindow(GetDlgItem(hWnd, pshHelp), SW_HIDE);
  if (ofn->Flags & OFN_HIDEREADONLY)
    ShowWindow(GetDlgItem(hWnd, chx1), SW_HIDE);
  if (lfs->hook)
      return FD31_CallWindowProc(lfs, WM_INITDIALOG, wParam, lfs->lParam);
  return TRUE;
}