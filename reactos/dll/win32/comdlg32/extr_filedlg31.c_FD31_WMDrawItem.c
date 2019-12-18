#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  char WCHAR ;
struct TYPE_6__ {scalar_t__ top; scalar_t__ left; } ;
struct TYPE_5__ {scalar_t__ CtlType; scalar_t__ CtlID; int itemState; TYPE_3__ rcItem; int /*<<< orphan*/  hDC; int /*<<< orphan*/  itemID; int /*<<< orphan*/  hwndItem; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HICON ;
typedef  TYPE_1__ DRAWITEMSTRUCT ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFILEALLOC ; 
 int /*<<< orphan*/  CB_GETLBTEXT ; 
 int /*<<< orphan*/  COLOR_GRAYTEXT ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHT ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHTTEXT ; 
 int /*<<< orphan*/  DI_NORMAL ; 
#define  DRIVE_CDROM 131 
#define  DRIVE_FIXED 130 
#define  DRIVE_REMOTE 129 
#define  DRIVE_REMOVABLE 128 
 int /*<<< orphan*/  DrawFocusRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  DrawIconEx (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETO_CLIPPED ; 
 int ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutW (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetDriveTypeA (char*) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int ODS_SELECTED ; 
 scalar_t__ ODT_COMBOBOX ; 
 scalar_t__ ODT_LISTBOX ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ cmb2 ; 
 scalar_t__ fldrWidth ; 
 int /*<<< orphan*/  hCDRom ; 
 int /*<<< orphan*/  hFloppy ; 
 int /*<<< orphan*/  hFolder ; 
 int /*<<< orphan*/  hHDisk ; 
 int /*<<< orphan*/  hNet ; 
 char* heap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 scalar_t__ lst1 ; 
 scalar_t__ lst2 ; 
 int /*<<< orphan*/  lstrlenW (char*) ; 

__attribute__((used)) static LONG FD31_WMDrawItem(HWND hWnd, WPARAM wParam, LPARAM lParam,
			    int savedlg, const DRAWITEMSTRUCT *lpdis)
{
    WCHAR *str;
    HICON hIcon;
    COLORREF oldText = 0, oldBk = 0;

    if (lpdis->CtlType == ODT_LISTBOX && lpdis->CtlID == lst1)
    {
        if (!(str = heap_alloc(BUFFILEALLOC))) return FALSE;
	SendMessageW(lpdis->hwndItem, LB_GETTEXT, lpdis->itemID,
                      (LPARAM)str);

	if ((lpdis->itemState & ODS_SELECTED) && !savedlg)
	{
	    oldBk = SetBkColor( lpdis->hDC, GetSysColor( COLOR_HIGHLIGHT ) );
	    oldText = SetTextColor( lpdis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	if (savedlg)
	    SetTextColor(lpdis->hDC,GetSysColor(COLOR_GRAYTEXT) );

	ExtTextOutW(lpdis->hDC, lpdis->rcItem.left + 1,
                  lpdis->rcItem.top + 1, ETO_OPAQUE | ETO_CLIPPED,
                  &(lpdis->rcItem), str, lstrlenW(str), NULL);

	if (lpdis->itemState & ODS_SELECTED)
	    DrawFocusRect( lpdis->hDC, &(lpdis->rcItem) );

	if ((lpdis->itemState & ODS_SELECTED) && !savedlg)
	{
	    SetBkColor( lpdis->hDC, oldBk );
	    SetTextColor( lpdis->hDC, oldText );
	}
        heap_free(str);
	return TRUE;
    }

    if (lpdis->CtlType == ODT_LISTBOX && lpdis->CtlID == lst2)
    {
        if (!(str = heap_alloc(BUFFILEALLOC)))
            return FALSE;
	SendMessageW(lpdis->hwndItem, LB_GETTEXT, lpdis->itemID,
                      (LPARAM)str);

	if (lpdis->itemState & ODS_SELECTED)
	{
	    oldBk = SetBkColor( lpdis->hDC, GetSysColor( COLOR_HIGHLIGHT ) );
	    oldText = SetTextColor( lpdis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	ExtTextOutW(lpdis->hDC, lpdis->rcItem.left + fldrWidth,
                  lpdis->rcItem.top + 1, ETO_OPAQUE | ETO_CLIPPED,
                  &(lpdis->rcItem), str, lstrlenW(str), NULL);

	if (lpdis->itemState & ODS_SELECTED)
	    DrawFocusRect( lpdis->hDC, &(lpdis->rcItem) );

	if (lpdis->itemState & ODS_SELECTED)
	{
	    SetBkColor( lpdis->hDC, oldBk );
	    SetTextColor( lpdis->hDC, oldText );
	}
	DrawIconEx( lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, hFolder, 16, 16, 0, 0, DI_NORMAL );
        heap_free(str);
	return TRUE;
    }
    if (lpdis->CtlType == ODT_COMBOBOX && lpdis->CtlID == cmb2)
    {
        char root[] = "a:";
        if (!(str = heap_alloc(BUFFILEALLOC)))
            return FALSE;
	SendMessageW(lpdis->hwndItem, CB_GETLBTEXT, lpdis->itemID,
                      (LPARAM)str);
        root[0] += str[2] - 'a';
        switch(GetDriveTypeA(root))
        {
        case DRIVE_REMOVABLE: hIcon = hFloppy; break;
        case DRIVE_CDROM:     hIcon = hCDRom; break;
        case DRIVE_REMOTE:    hIcon = hNet; break;
        case DRIVE_FIXED:
        default:           hIcon = hHDisk; break;
        }
	if (lpdis->itemState & ODS_SELECTED)
	{
	    oldBk = SetBkColor( lpdis->hDC, GetSysColor( COLOR_HIGHLIGHT ) );
	    oldText = SetTextColor( lpdis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	ExtTextOutW(lpdis->hDC, lpdis->rcItem.left + fldrWidth,
                  lpdis->rcItem.top + 1, ETO_OPAQUE | ETO_CLIPPED,
                  &(lpdis->rcItem), str, lstrlenW(str), NULL);

	if (lpdis->itemState & ODS_SELECTED)
	{
	    SetBkColor( lpdis->hDC, oldBk );
	    SetTextColor( lpdis->hDC, oldText );
	}
	DrawIconEx( lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, hIcon, 16, 16, 0, 0, DI_NORMAL );
        heap_free(str);
	return TRUE;
    }
    return FALSE;
}