#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ UINT ;
struct TYPE_14__ {int bottom; int top; int right; scalar_t__ left; } ;
struct TYPE_15__ {int itemID; int /*<<< orphan*/  CtlID; scalar_t__ itemData; TYPE_3__ rcItem; int /*<<< orphan*/  hDC; int /*<<< orphan*/  hwndItem; } ;
struct TYPE_13__ {int style; scalar_t__ text; int /*<<< orphan*/  hIcon; TYPE_3__ bound; } ;
struct TYPE_12__ {int numParts; int /*<<< orphan*/  Notify; int /*<<< orphan*/  Self; scalar_t__ simple; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  TYPE_2__ STATUSWINDOWPART ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  scalar_t__ HTHEME ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_4__ DRAWITEMSTRUCT ;

/* Variables and functions */
 scalar_t__ BDR_RAISEDOUTER ; 
 scalar_t__ BDR_SUNKENOUTER ; 
 int BF_ADJUST ; 
 int BF_RECT ; 
 int /*<<< orphan*/  DI_NORMAL ; 
 int DT_NOPREFIX ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  DrawIconEx (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawStatusTextW (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  DrawThemeBackground (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DrawThemeText (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int SBARS_SIZEGRIP ; 
 int SBT_NOBORDERS ; 
 int SBT_OWNERDRAW ; 
 int SBT_POPOUT ; 
 int SP_GRIPPERPANE ; 
 int SP_PANE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_DRAWITEM ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_3__*) ; 

__attribute__((used)) static void
STATUSBAR_DrawPart (const STATUS_INFO *infoPtr, HDC hdc, const STATUSWINDOWPART *part, int itemID)
{
    RECT r = part->bound;
    UINT border = BDR_SUNKENOUTER;
    HTHEME theme = GetWindowTheme (infoPtr->Self);
    int themePart = SP_PANE;
    int x = 0;

    TRACE("part bound %s\n", wine_dbgstr_rect(&r));
    if (part->style & SBT_POPOUT)
        border = BDR_RAISEDOUTER;
    else if (part->style & SBT_NOBORDERS)
        border = 0;

    if (theme)
    {
        if ((GetWindowLongW (infoPtr->Self, GWL_STYLE) & SBARS_SIZEGRIP)
            && (infoPtr->simple || (itemID == (infoPtr->numParts-1))))
            themePart = SP_GRIPPERPANE;
        DrawThemeBackground(theme, hdc, themePart, 0, &r, NULL);
    }
    else
        DrawEdge(hdc, &r, border, BF_RECT|BF_ADJUST);

    if (part->hIcon) {
        INT cy = r.bottom - r.top;
        DrawIconEx (hdc, r.left + 2, r.top, part->hIcon, cy, cy, 0, 0, DI_NORMAL);
        x = 2 + cy;
    }

    if (part->style & SBT_OWNERDRAW) {
	DRAWITEMSTRUCT dis;

	dis.CtlID = GetWindowLongPtrW (infoPtr->Self, GWLP_ID);
	dis.itemID = itemID;
	dis.hwndItem = infoPtr->Self;
	dis.hDC = hdc;
	dis.rcItem = r;
	dis.itemData = (ULONG_PTR)part->text;
        SendMessageW (infoPtr->Notify, WM_DRAWITEM, dis.CtlID, (LPARAM)&dis);
    } else {
        r.left += x;
#ifdef __REACTOS__
        if (!theme)
        {
            r.left -= 2;
            DrawStatusTextW (hdc, &r, part->text, SBT_NOBORDERS);
        }
        else
        {
            r.left += 2;
            r.right -= 2;
            DrawThemeText(theme, hdc, SP_PANE, 0, part->text, -1, DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX, 0, &r);
        }
#else
        DrawStatusTextW (hdc, &r, part->text, SBT_NOBORDERS);
#endif
    }
}