#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ cy; scalar_t__ cx; } ;
struct TYPE_12__ {TYPE_4__* lpBrowseInfo; scalar_t__ hwndTreeView; int /*<<< orphan*/ * layout; TYPE_1__ szMin; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_2__ browse_info ;
struct TYPE_14__ {int ulFlags; scalar_t__ lpszTitle; } ;
struct TYPE_13__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__* LPBROWSEINFOW ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BFFM_INITIALIZED ; 
 int BIF_EDITBOX ; 
 int BIF_NEWDIALOGSTYLE ; 
 int BIF_NONEWFOLDERBUTTON ; 
 int BIF_STATUSTEXT ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_3__*) ; 
 scalar_t__ GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  HWND_TOP ; 
 int /*<<< orphan*/  IDC_BROWSE_FOR_FOLDER_FOLDER ; 
 int /*<<< orphan*/  IDC_BROWSE_FOR_FOLDER_FOLDER_TEXT ; 
 int /*<<< orphan*/  IDC_BROWSE_FOR_FOLDER_NEW_FOLDER ; 
 int /*<<< orphan*/  IDC_BROWSE_FOR_FOLDER_STATUS ; 
 int /*<<< orphan*/  IDC_BROWSE_FOR_FOLDER_TITLE ; 
 int /*<<< orphan*/  IDC_BROWSE_FOR_FOLDER_TREEVIEW ; 
 int /*<<< orphan*/  InitializeTreeView (TYPE_2__*) ; 
 int /*<<< orphan*/  LAYOUT_INFO_COUNT ; 
 int /*<<< orphan*/ * LayoutInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SUPPORTEDFLAGS ; 
 int /*<<< orphan*/  SWP_NOMOVE ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowTextW (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  browsefolder_callback (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_layout_info ; 
 int /*<<< orphan*/  szBrowseFolderInfo ; 

__attribute__((used)) static BOOL BrsFolder_OnCreate( HWND hWnd, browse_info *info )
{
    LPBROWSEINFOW lpBrowseInfo = info->lpBrowseInfo;

    info->hWnd = hWnd;
    SetPropW( hWnd, szBrowseFolderInfo, info );

    if (lpBrowseInfo->ulFlags & BIF_NEWDIALOGSTYLE)
        FIXME("flags BIF_NEWDIALOGSTYLE partially implemented\n");
    if (lpBrowseInfo->ulFlags & ~SUPPORTEDFLAGS)
	FIXME("flags %x not implemented\n", lpBrowseInfo->ulFlags & ~SUPPORTEDFLAGS);

    if (lpBrowseInfo->ulFlags & BIF_NEWDIALOGSTYLE)
    {
        RECT rcWnd;

        info->layout = LayoutInit(hWnd, g_layout_info, LAYOUT_INFO_COUNT);

        /* TODO: Windows allows shrinking the windows a bit */
        GetWindowRect(hWnd, &rcWnd);
        info->szMin.cx = rcWnd.right - rcWnd.left;
        info->szMin.cy = rcWnd.bottom - rcWnd.top;
    }
    else
    {
        info->layout = NULL;
    }

    if (lpBrowseInfo->lpszTitle)
	SetWindowTextW( GetDlgItem(hWnd, IDC_BROWSE_FOR_FOLDER_TITLE), lpBrowseInfo->lpszTitle );
    else
	ShowWindow( GetDlgItem(hWnd, IDC_BROWSE_FOR_FOLDER_TITLE), SW_HIDE );

    if (!(lpBrowseInfo->ulFlags & BIF_STATUSTEXT)
        || (lpBrowseInfo->ulFlags & BIF_NEWDIALOGSTYLE))
	ShowWindow( GetDlgItem(hWnd, IDC_BROWSE_FOR_FOLDER_STATUS), SW_HIDE );

    /* Hide "Make New Folder" Button? */
    if ((lpBrowseInfo->ulFlags & BIF_NONEWFOLDERBUTTON)
        || !(lpBrowseInfo->ulFlags & BIF_NEWDIALOGSTYLE))
        ShowWindow( GetDlgItem(hWnd, IDC_BROWSE_FOR_FOLDER_NEW_FOLDER), SW_HIDE );

    /* Hide the editbox? */
    if (!(lpBrowseInfo->ulFlags & BIF_EDITBOX))
    {
        ShowWindow( GetDlgItem(hWnd, IDC_BROWSE_FOR_FOLDER_FOLDER), SW_HIDE );
        ShowWindow( GetDlgItem(hWnd, IDC_BROWSE_FOR_FOLDER_FOLDER_TEXT), SW_HIDE );
    }

    info->hwndTreeView = GetDlgItem( hWnd, IDC_BROWSE_FOR_FOLDER_TREEVIEW );
    if (info->hwndTreeView)
    {
        InitializeTreeView( info );

        /* Resize the treeview if there's not editbox */
        if ((lpBrowseInfo->ulFlags & BIF_NEWDIALOGSTYLE)
            && !(lpBrowseInfo->ulFlags & BIF_EDITBOX))
        {
            RECT rc;
            GetClientRect(info->hwndTreeView, &rc);
            SetWindowPos(info->hwndTreeView, HWND_TOP, 0, 0,
                         rc.right, rc.bottom + 40, SWP_NOMOVE);
        }
    }
    else
        ERR("treeview control missing!\n");

    browsefolder_callback( info->lpBrowseInfo, hWnd, BFFM_INITIALIZED, 0 );

    return TRUE;
}