#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_10__ {TYPE_3__ mines_rect; TYPE_3__ face_rect; TYPE_3__ timer_rect; scalar_t__ time; TYPE_3__ counter_rect; scalar_t__ num_flags; scalar_t__ mines; } ;
struct TYPE_9__ {int /*<<< orphan*/  rcPaint; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ PAINTSTRUCT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_2__ BOARD ;

/* Variables and functions */
 int /*<<< orphan*/  DrawFace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DrawLeds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawMines (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ IntersectRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void DrawBoard( HDC hdc, HDC hMemDC, PAINTSTRUCT *ps, BOARD *p_board )
{
    RECT tmp_rect;

    if( IntersectRect( &tmp_rect, &ps->rcPaint, &p_board->counter_rect ) )
        DrawLeds( hdc, hMemDC, p_board, p_board->mines - p_board->num_flags,
                  p_board->counter_rect.left,
                  p_board->counter_rect.top );

    if( IntersectRect( &tmp_rect, &ps->rcPaint, &p_board->timer_rect ) )
        DrawLeds( hdc, hMemDC, p_board, p_board->time,
                  p_board->timer_rect.left,
                  p_board->timer_rect.top );

    if( IntersectRect( &tmp_rect, &ps->rcPaint, &p_board->face_rect ) )
        DrawFace( hdc, hMemDC, p_board );

    if( IntersectRect( &tmp_rect, &ps->rcPaint, &p_board->mines_rect ) )
        DrawMines( hdc, hMemDC, p_board );
}