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
typedef  int UINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  FD31_DATA ;

/* Variables and functions */
 int CBN_SELCHANGE ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FD31_DirListDblClick (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  FD31_DiskChange (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  FD31_FileListSelect (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  FD31_FileTypeChange (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  FD31_StripEditControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FD31_Validate (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IDABORT 136 
#define  IDCANCEL 135 
#define  IDOK 134 
 int LBN_DBLCLK ; 
 int LBN_SELCHANGE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_COMMAND ; 
#define  chx1 133 
#define  cmb1 132 
#define  cmb2 131 
#define  lst1 130 
#define  lst2 129 
#define  pshHelp 128 

__attribute__((used)) static LRESULT FD31_WMCommand( HWND hWnd, LPARAM lParam, UINT notification,
			       UINT control, const FD31_DATA *lfs )
{
    switch (control)
    {
        case lst1: /* file list */
        FD31_StripEditControl(hWnd);
        if (notification == LBN_DBLCLK)
        {
            return SendMessageW(hWnd, WM_COMMAND, IDOK, 0);
        }
        else if (notification == LBN_SELCHANGE)
            return FD31_FileListSelect( lfs );
        break;

        case lst2: /* directory list */
        FD31_StripEditControl(hWnd);
        if (notification == LBN_DBLCLK)
            return FD31_DirListDblClick( lfs );
        break;

        case cmb1: /* file type drop list */
        if (notification == CBN_SELCHANGE)
            return FD31_FileTypeChange( lfs );
        break;

        case chx1:
        break;

        case pshHelp:
        break;

        case cmb2: /* disk dropdown combo */
        if (notification == CBN_SELCHANGE)
            return FD31_DiskChange( lfs );
        break;

        case IDOK:
        TRACE("OK pressed\n");
        if (FD31_Validate( lfs, NULL, control, 0, FALSE ))
            EndDialog(hWnd, TRUE);
        return TRUE;

        case IDCANCEL:
        EndDialog(hWnd, FALSE);
        return TRUE;

        case IDABORT: /* can be sent by the hook procedure */
        EndDialog(hWnd, TRUE);
        return TRUE;
    }
    return FALSE;
}