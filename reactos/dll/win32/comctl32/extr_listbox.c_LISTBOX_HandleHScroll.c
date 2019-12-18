#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
typedef  int WORD ;
struct TYPE_8__ {int style; int top_item; int page_size; int width; int column_width; int nb_items; int horz_extent; int horz_pos; int /*<<< orphan*/  self; } ;
struct TYPE_7__ {int cbSize; int nTrackPos; void* fMask; } ;
typedef  TYPE_1__ SCROLLINFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ LB_DESCR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int LBS_MULTICOLUMN ; 
 int /*<<< orphan*/  LISTBOX_SetHorizontalPos (TYPE_2__*,int) ; 
 int /*<<< orphan*/  LISTBOX_SetTopItem (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_HORZ ; 
#define  SB_LEFT 135 
#define  SB_LINELEFT 134 
#define  SB_LINERIGHT 133 
#define  SB_PAGELEFT 132 
#define  SB_PAGERIGHT 131 
#define  SB_RIGHT 130 
#define  SB_THUMBPOSITION 129 
#define  SB_THUMBTRACK 128 
 int /*<<< orphan*/  SB_VERT ; 
 void* SIF_TRACKPOS ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT LISTBOX_HandleHScroll( LB_DESCR *descr, WORD scrollReq, WORD pos )
{
    SCROLLINFO info;
    INT page;

    if (descr->style & LBS_MULTICOLUMN)
    {
        switch(scrollReq)
        {
        case SB_LINELEFT:
            LISTBOX_SetTopItem( descr, descr->top_item-descr->page_size,
                                TRUE );
            break;
        case SB_LINERIGHT:
            LISTBOX_SetTopItem( descr, descr->top_item+descr->page_size,
                                TRUE );
            break;
        case SB_PAGELEFT:
            page = descr->width / descr->column_width;
            if (page < 1) page = 1;
            LISTBOX_SetTopItem( descr,
                             descr->top_item - page * descr->page_size, TRUE );
            break;
        case SB_PAGERIGHT:
            page = descr->width / descr->column_width;
            if (page < 1) page = 1;
            LISTBOX_SetTopItem( descr,
                             descr->top_item + page * descr->page_size, TRUE );
            break;
        case SB_THUMBPOSITION:
            LISTBOX_SetTopItem( descr, pos*descr->page_size, TRUE );
            break;
        case SB_THUMBTRACK:
            info.cbSize = sizeof(info);
            info.fMask  = SIF_TRACKPOS;
            GetScrollInfo( descr->self, SB_VERT, &info );
            LISTBOX_SetTopItem( descr, info.nTrackPos*descr->page_size,
                                TRUE );
            break;
        case SB_LEFT:
            LISTBOX_SetTopItem( descr, 0, TRUE );
            break;
        case SB_RIGHT:
            LISTBOX_SetTopItem( descr, descr->nb_items, TRUE );
            break;
        }
    }
    else if (descr->horz_extent)
    {
        switch(scrollReq)
        {
        case SB_LINELEFT:
            LISTBOX_SetHorizontalPos( descr, descr->horz_pos - 1 );
            break;
        case SB_LINERIGHT:
            LISTBOX_SetHorizontalPos( descr, descr->horz_pos + 1 );
            break;
        case SB_PAGELEFT:
            LISTBOX_SetHorizontalPos( descr,
                                      descr->horz_pos - descr->width );
            break;
        case SB_PAGERIGHT:
            LISTBOX_SetHorizontalPos( descr,
                                      descr->horz_pos + descr->width );
            break;
        case SB_THUMBPOSITION:
            LISTBOX_SetHorizontalPos( descr, pos );
            break;
        case SB_THUMBTRACK:
            info.cbSize = sizeof(info);
            info.fMask = SIF_TRACKPOS;
            GetScrollInfo( descr->self, SB_HORZ, &info );
            LISTBOX_SetHorizontalPos( descr, info.nTrackPos );
            break;
        case SB_LEFT:
            LISTBOX_SetHorizontalPos( descr, 0 );
            break;
        case SB_RIGHT:
            LISTBOX_SetHorizontalPos( descr,
                                      descr->horz_extent - descr->width );
            break;
        }
    }
    return 0;
}