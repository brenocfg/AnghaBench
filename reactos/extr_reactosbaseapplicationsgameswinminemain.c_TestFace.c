#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  face_rect; int /*<<< orphan*/  hWnd; int /*<<< orphan*/  face_bmp; } ;
typedef  int /*<<< orphan*/  POINT ;
typedef  TYPE_1__ BOARD ;

/* Variables and functions */
 int /*<<< orphan*/  COOL_BMP ; 
 int /*<<< orphan*/  CreateBoard (TYPE_1__*) ; 
 int /*<<< orphan*/  DEAD_BMP ; 
 scalar_t__ GAMEOVER ; 
 int /*<<< orphan*/  OOH_BMP ; 
 scalar_t__ PLAYING ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RDW_INVALIDATE ; 
 int RDW_UPDATENOW ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SMILE_BMP ; 
 int /*<<< orphan*/  SPRESS_BMP ; 
 scalar_t__ WAITING ; 
 int WM_LBUTTONDOWN ; 
 int WM_LBUTTONUP ; 
 int WM_MBUTTONDOWN ; 
 scalar_t__ WON ; 

__attribute__((used)) static void TestFace( BOARD *p_board, POINT pt, int msg )
{
    if( p_board->status == PLAYING || p_board->status == WAITING ) {
        if( msg == WM_LBUTTONDOWN || msg == WM_MBUTTONDOWN )
            p_board->face_bmp = OOH_BMP;
        else p_board->face_bmp = SMILE_BMP;
    }
    else if( p_board->status == GAMEOVER )
        p_board->face_bmp = DEAD_BMP;
    else if( p_board->status == WON )
            p_board->face_bmp = COOL_BMP;

    if( PtInRect( &p_board->face_rect, pt ) ) {
        if( msg == WM_LBUTTONDOWN )
            p_board->face_bmp = SPRESS_BMP;

        if( msg == WM_LBUTTONUP )
            CreateBoard( p_board );
    }

    RedrawWindow( p_board->hWnd, &p_board->face_rect, 0,
        RDW_INVALIDATE | RDW_UPDATENOW );
}