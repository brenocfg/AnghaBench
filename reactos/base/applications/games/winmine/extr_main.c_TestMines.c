#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int x; int y; } ;
struct TYPE_16__ {int left; int top; } ;
struct TYPE_20__ {int /*<<< orphan*/  hWnd; TYPE_3__ press; int /*<<< orphan*/  status; TYPE_2__** box; TYPE_1__ mines_rect; } ;
struct TYPE_19__ {int x; int y; } ;
struct TYPE_17__ {int /*<<< orphan*/  FlagType; } ;
typedef  TYPE_4__ POINT ;
typedef  scalar_t__ BOOL ;
typedef  TYPE_5__ BOARD ;

/* Variables and functions */
 int /*<<< orphan*/  AddFlag (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  CompleteBox (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  CompleteBoxes (TYPE_5__*,int,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FLAG ; 
 int MINE_HEIGHT ; 
 int MINE_WIDTH ; 
 int /*<<< orphan*/  PLAYING ; 
 int /*<<< orphan*/  PlaceMines (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  PressBox (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  PressBoxes (TYPE_5__*,int,int) ; 
 int RDW_INVALIDATE ; 
 int RDW_UPDATENOW ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UnpressBox (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  UnpressBoxes (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  WINE_TRACE (char*) ; 
#define  WM_LBUTTONDOWN 132 
#define  WM_LBUTTONUP 131 
#define  WM_MBUTTONDOWN 130 
#define  WM_MBUTTONUP 129 
#define  WM_RBUTTONDOWN 128 

__attribute__((used)) static void TestMines( BOARD *p_board, POINT pt, int msg )
{
    BOOL draw = TRUE;
    int col, row;

    col = (pt.x - p_board->mines_rect.left) / MINE_WIDTH + 1;
    row = (pt.y - p_board->mines_rect.top ) / MINE_HEIGHT + 1;

    switch ( msg ) {
    case WM_LBUTTONDOWN:
        if( p_board->press.x != col || p_board->press.y != row ) {
            UnpressBox( p_board,
                    p_board->press.x, p_board->press.y );
            p_board->press.x = col;
            p_board->press.y = row;
            PressBox( p_board, col, row );
        }
        draw = FALSE;
        break;

    case WM_LBUTTONUP:
        if( p_board->press.x != col || p_board->press.y != row )
            UnpressBox( p_board,
                    p_board->press.x, p_board->press.y );
        p_board->press.x = 0;
        p_board->press.y = 0;
        if( p_board->box[col][row].FlagType != FLAG
            && p_board->status != PLAYING )
        {
            p_board->status = PLAYING;
            PlaceMines( p_board, col, row );
        }
        CompleteBox( p_board, col, row );
        break;

    case WM_MBUTTONDOWN:
        PressBoxes( p_board, col, row );
        draw = FALSE;
        break;

    case WM_MBUTTONUP:
        if( p_board->press.x != col || p_board->press.y != row )
            UnpressBoxes( p_board,
                    p_board->press.x, p_board->press.y );
        p_board->press.x = 0;
        p_board->press.y = 0;
        CompleteBoxes( p_board, col, row );
        break;

    case WM_RBUTTONDOWN:
        AddFlag( p_board, col, row );
        break;
    default:
        WINE_TRACE("Unknown message type received in TestMines\n");
        break;
    }

    if( draw )
    {
        RedrawWindow( p_board->hWnd, NULL, 0,
            RDW_INVALIDATE | RDW_UPDATENOW );
    }
}