#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lf ;
typedef  int UINT ;
struct TYPE_12__ {int /*<<< orphan*/ * crColor; } ;
struct TYPE_11__ {int /*<<< orphan*/  lfFaceName; int /*<<< orphan*/  lfCharSet; int /*<<< orphan*/  lfWeight; scalar_t__ lfWidth; scalar_t__ lfHeight; } ;
struct TYPE_10__ {int right; scalar_t__ top; scalar_t__ left; scalar_t__ bottom; } ;
typedef  char TCHAR ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPRECT ;
typedef  TYPE_2__ LOGFONT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_3__ COLOR_SCHEME ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BF_MIDDLE ; 
 int BF_RECT ; 
 size_t COLOR_BTNHIGHLIGHT ; 
 size_t COLOR_BTNSHADOW ; 
 size_t COLOR_BTNTEXT ; 
 int /*<<< orphan*/  CreateFontIndirect (TYPE_2__*) ; 
 int /*<<< orphan*/  DEFAULT_CHARSET ; 
 int DFCS_FLAT ; 
 int DFCS_INACTIVE ; 
 int DFCS_PUSHED ; 
#define  DFCS_SCROLLCOMBOBOX 132 
#define  DFCS_SCROLLDOWN 131 
#define  DFCS_SCROLLLEFT 130 
#define  DFCS_SCROLLRIGHT 129 
#define  DFCS_SCROLLUP 128 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDGE_RAISED ; 
 int /*<<< orphan*/  EDGE_SUNKEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FW_NORMAL ; 
 int /*<<< orphan*/  GetBkMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyIntDrawRectEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  MyMakeSquareRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRANSPARENT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
MyDrawFrameScroll(HDC dc, LPRECT r, UINT uFlags, COLOR_SCHEME *scheme)
{
    LOGFONT lf;
    HFONT hFont, hOldFont;
    COLORREF clrsave;
    RECT myr;
    INT bkmode;
    TCHAR Symbol;
    switch(uFlags & 0xff)
    {
    case DFCS_SCROLLCOMBOBOX:
    case DFCS_SCROLLDOWN:
        Symbol = '6';
        break;

    case DFCS_SCROLLUP:
        Symbol = '5';
        break;

    case DFCS_SCROLLLEFT:
        Symbol = '3';
        break;

    case DFCS_SCROLLRIGHT:
        Symbol = '4';
        break;

    default:
        return FALSE;
    }
    MyIntDrawRectEdge(dc, r, (uFlags & DFCS_PUSHED) ? EDGE_SUNKEN : EDGE_RAISED, (uFlags&DFCS_FLAT) | BF_MIDDLE | BF_RECT, scheme);
    ZeroMemory(&lf, sizeof(lf));
    MyMakeSquareRect(r, &myr);
    myr.left += 1;
    myr.top += 1;
    myr.right -= 1;
    myr.bottom -= 1;
    if (uFlags & DFCS_PUSHED)
       OffsetRect(&myr,1,1);
    lf.lfHeight = myr.bottom - myr.top;
    lf.lfWidth = 0;
    lf.lfWeight = FW_NORMAL;
    lf.lfCharSet = DEFAULT_CHARSET;
    lstrcpy(lf.lfFaceName, TEXT("Marlett"));
    hFont = CreateFontIndirect(&lf);
    /* Save font and text color */
    hOldFont = SelectObject(dc, hFont);
    clrsave = GetTextColor(dc);
    bkmode = GetBkMode(dc);
    /* Set color and drawing mode */
    SetBkMode(dc, TRANSPARENT);
    if (uFlags & DFCS_INACTIVE)
    {
        /* Draw shadow */
        SetTextColor(dc, scheme->crColor[COLOR_BTNHIGHLIGHT]);
        TextOut(dc, myr.left + 1, myr.top + 1, &Symbol, 1);
    }
    SetTextColor(dc, scheme->crColor[(uFlags & DFCS_INACTIVE) ? COLOR_BTNSHADOW : COLOR_BTNTEXT]);
    /* Draw selected symbol */
    TextOut(dc, myr.left, myr.top, &Symbol, 1);
    /* restore previous settings */
    SetTextColor(dc, clrsave);
    SelectObject(dc, hOldFont);
    SetBkMode(dc, bkmode);
    DeleteObject(hFont);
    return TRUE;
}