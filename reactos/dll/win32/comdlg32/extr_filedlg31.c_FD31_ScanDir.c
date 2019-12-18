#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_3__ {scalar_t__ nFilterIndex; int /*<<< orphan*/  lpstrFilter; int /*<<< orphan*/  lpstrCustomFilter; } ;
typedef  TYPE_1__ OPENFILENAMEW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HCURSOR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BUFFILE ; 
 int DDL_DIRECTORY ; 
 int DDL_EXCLUSIVE ; 
 int /*<<< orphan*/  DlgDirListW (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FD31_GetFileType (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FILE_star ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_WAIT ; 
 int /*<<< orphan*/  LB_DIR ; 
 int /*<<< orphan*/  LB_RESETCONTENT ; 
 int /*<<< orphan*/  LoadCursorA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCurrentDirectoryW (char*) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  lst1 ; 
 int /*<<< orphan*/  lst2 ; 
 int /*<<< orphan*/  lstrcpyW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpynW (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stc1 ; 
 char* wcschr (char*,char) ; 

__attribute__((used)) static BOOL FD31_ScanDir(const OPENFILENAMEW *ofn, HWND hWnd, LPCWSTR newPath)
{
    WCHAR   buffer[BUFFILE];
    HWND    hdlg;
    LRESULT lRet = TRUE;
    HCURSOR hCursorWait, oldCursor;

    TRACE("Trying to change to %s\n", debugstr_w(newPath));
    if  ( newPath[0] && !SetCurrentDirectoryW( newPath ))
        return FALSE;

    /* get the list of spec files */
    lstrcpynW(buffer, FD31_GetFileType(ofn->lpstrCustomFilter,
              ofn->lpstrFilter, ofn->nFilterIndex - 1), BUFFILE);

    hCursorWait = LoadCursorA(0, (LPSTR)IDC_WAIT);
    oldCursor = SetCursor(hCursorWait);

    /* list of files */
    if ((hdlg = GetDlgItem(hWnd, lst1)) != 0) {
        WCHAR*	scptr; /* ptr on semi-colon */
	WCHAR*	filter = buffer;

	TRACE("Using filter %s\n", debugstr_w(filter));
	SendMessageW(hdlg, LB_RESETCONTENT, 0, 0);
	while (filter) {
	    scptr = wcschr(filter, ';');
	    if (scptr)	*scptr = 0;
	    while (*filter == ' ') filter++;
	    TRACE("Using file spec %s\n", debugstr_w(filter));
	    SendMessageW(hdlg, LB_DIR, 0, (LPARAM)filter);
	    if (scptr) *scptr = ';';
	    filter = (scptr) ? (scptr + 1) : 0;
	 }
    }

    /* list of directories */
    lstrcpyW(buffer, FILE_star);

    if (GetDlgItem(hWnd, lst2) != 0) {
        lRet = DlgDirListW(hWnd, buffer, lst2, stc1, DDL_EXCLUSIVE | DDL_DIRECTORY);
    }
    SetCursor(oldCursor);
    return lRet;
}