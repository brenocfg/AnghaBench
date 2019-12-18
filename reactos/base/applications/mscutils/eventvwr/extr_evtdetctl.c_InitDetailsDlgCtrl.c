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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ hMonospaceFont; scalar_t__ bDisplayWords; } ;
typedef  TYPE_1__* PDETAILDATA ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AURL_ENABLEURL ; 
 int /*<<< orphan*/  BM_SETCHECK ; 
 int /*<<< orphan*/  BM_SETIMAGE ; 
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  COLOR_3DFACE ; 
 int /*<<< orphan*/  EM_AUTOURLDETECT ; 
 int /*<<< orphan*/  EM_GETEVENTMASK ; 
 int /*<<< orphan*/  EM_SETBKGNDCOLOR ; 
 int /*<<< orphan*/  EM_SETEVENTMASK ; 
 int ENM_LINK ; 
 int ENM_MOUSEEVENTS ; 
 int GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_BYTESRADIO ; 
 int /*<<< orphan*/  IDC_COPY ; 
 int /*<<< orphan*/  IDC_EVENTDATAEDIT ; 
 int /*<<< orphan*/  IDC_EVENTTEXTEDIT ; 
 int /*<<< orphan*/  IDC_NEXT ; 
 int /*<<< orphan*/  IDC_PREVIOUS ; 
 int /*<<< orphan*/  IDC_WORDRADIO ; 
 int /*<<< orphan*/  IDI_COPY ; 
 int /*<<< orphan*/  IDI_NEXT ; 
 int /*<<< orphan*/  IDI_PREV ; 
 scalar_t__ IMAGE_ICON ; 
 int /*<<< orphan*/  LR_DEFAULTCOLOR ; 
 scalar_t__ LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int /*<<< orphan*/  hInst ; 

__attribute__((used)) static
VOID
InitDetailsDlgCtrl(HWND hDlg, PDETAILDATA pData)
{
    DWORD dwMask;

    HANDLE nextIcon = LoadImageW(hInst, MAKEINTRESOURCEW(IDI_NEXT), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    HANDLE prevIcon = LoadImageW(hInst, MAKEINTRESOURCEW(IDI_PREV), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    HANDLE copyIcon = LoadImageW(hInst, MAKEINTRESOURCEW(IDI_COPY), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

    SendDlgItemMessageW(hDlg, IDC_NEXT, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)nextIcon);
    SendDlgItemMessageW(hDlg, IDC_PREVIOUS, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)prevIcon);
    SendDlgItemMessageW(hDlg, IDC_COPY, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)copyIcon);

    /* Set the default read-only RichEdit color */
    SendDlgItemMessageW(hDlg, IDC_EVENTTEXTEDIT, EM_SETBKGNDCOLOR, 0, GetSysColor(COLOR_3DFACE));

    /* Enable RichEdit coloured and underlined links */
    dwMask = SendDlgItemMessageW(hDlg, IDC_EVENTTEXTEDIT, EM_GETEVENTMASK, 0, 0);
    SendDlgItemMessageW(hDlg, IDC_EVENTTEXTEDIT, EM_SETEVENTMASK, 0, dwMask | ENM_LINK | ENM_MOUSEEVENTS);

    /*
     * Activate automatic URL recognition by the RichEdit control. For more information, see:
     * https://blogs.msdn.microsoft.com/murrays/2009/08/31/automatic-richedit-hyperlinks/
     * https://blogs.msdn.microsoft.com/murrays/2009/09/24/richedit-friendly-name-hyperlinks/
     * https://msdn.microsoft.com/en-us/library/windows/desktop/bb787991(v=vs.85).aspx
     */
    SendDlgItemMessageW(hDlg, IDC_EVENTTEXTEDIT, EM_AUTOURLDETECT, AURL_ENABLEURL /* | AURL_ENABLEEAURLS */, 0);

    /* Note that the RichEdit control never gets themed under WinXP+; one would have to write code to simulate Edit-control theming */

    SendDlgItemMessageW(hDlg, pData->bDisplayWords ? IDC_WORDRADIO : IDC_BYTESRADIO, BM_SETCHECK, BST_CHECKED, 0);
    SendDlgItemMessageW(hDlg, IDC_EVENTDATAEDIT, WM_SETFONT, (WPARAM)pData->hMonospaceFont, (LPARAM)TRUE);
}