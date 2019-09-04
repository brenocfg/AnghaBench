#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int x; int y; } ;
struct TYPE_9__ {TYPE_2__ press; TYPE_1__** box; } ;
struct TYPE_7__ {scalar_t__ IsPressed; } ;
typedef  TYPE_3__ BOARD ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PressBox (TYPE_3__*,unsigned int,unsigned int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UnpressBox (TYPE_3__*,int,int) ; 

__attribute__((used)) static void PressBoxes( BOARD *p_board, unsigned col, unsigned row )
{
    int i, j;

    for( i = -1; i <= 1; i++ )
      for( j = -1; j <= 1; j++ ) {
        p_board->box[col + i][row + j].IsPressed = TRUE;
        PressBox( p_board, col + i, row + j );
    }

    for( i = -1; i <= 1; i++ )
      for( j = -1; j <= 1; j++ ) {
        if( !p_board->box[p_board->press.x + i][p_board->press.y + j].IsPressed )
            UnpressBox( p_board, p_board->press.x + i, p_board->press.y + j );
    }

    for( i = -1; i <= 1; i++ )
      for( j = -1; j <= 1; j++ ) {
        p_board->box[col + i][row + j].IsPressed = FALSE;
        PressBox( p_board, col + i, row + j );
    }

    p_board->press.x = col;
    p_board->press.y = row;
}