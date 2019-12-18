#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_14__ {TYPE_1__* editor; int /*<<< orphan*/  hDC; } ;
struct TYPE_13__ {scalar_t__ nWidth; int /*<<< orphan*/  style; } ;
struct TYPE_12__ {int styleFlags; int /*<<< orphan*/  texthost; scalar_t__ bEmulateVersion10; int /*<<< orphan*/  bHaveFocus; scalar_t__ bHideSelection; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_2__ ME_Run ;
typedef  TYPE_3__ ME_Context ;
typedef  int /*<<< orphan*/ * HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_HIGHLIGHT ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSTINVERT ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int ES_NOHIDESEL ; 
 int /*<<< orphan*/  ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutW (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int,scalar_t__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_TxGetSysColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ME_SelectStyleFont (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_UnselectStyleFont (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PatBlt (int /*<<< orphan*/ ,int,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int calc_y_offset (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_underline (TYPE_3__*,TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_text_color (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void draw_space( ME_Context *c, ME_Run *run, int x, int y,
                        BOOL selected, BOOL actually_draw, int ymin, int cy )
{
    HDC hdc = c->hDC;
    BOOL old_style_selected = FALSE;
    RECT rect;
    COLORREF back_color = 0;

    SetRect( &rect, x, ymin, x + run->nWidth, ymin + cy );

    if (c->editor->bHideSelection || (!c->editor->bHaveFocus &&
                !(c->editor->styleFlags & ES_NOHIDESEL))) selected = FALSE;
    if (c->editor->bEmulateVersion10)
    {
        old_style_selected = selected;
        selected = FALSE;
    }

    if (selected)
        back_color = ITextHost_TxGetSysColor( c->editor->texthost, COLOR_HIGHLIGHT );

    if (actually_draw)
    {
        COLORREF text_color = get_text_color( c, run->style, selected );
        COLORREF old_text, old_back;
        HFONT old_font = NULL;
        int y_offset = calc_y_offset( c, run->style );
        static const WCHAR space[1] = {' '};

        old_font = ME_SelectStyleFont( c, run->style );
        old_text = SetTextColor( hdc, text_color );
        if (selected) old_back = SetBkColor( hdc, back_color );

        ExtTextOutW( hdc, x, y - y_offset, selected ? ETO_OPAQUE : 0, &rect, space, 1, &run->nWidth );

        if (selected) SetBkColor( hdc, old_back );
        SetTextColor( hdc, old_text );
        ME_UnselectStyleFont( c, run->style, old_font );

        draw_underline( c, run, x, y - y_offset, text_color );
    }
    else if (selected)
    {
        HBRUSH brush = CreateSolidBrush( back_color );
        FillRect( hdc, &rect, brush );
        DeleteObject( brush );
    }

    if (old_style_selected)
        PatBlt( hdc, x, ymin, run->nWidth, cy, DSTINVERT );
}