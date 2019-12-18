#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cols; int rows; scalar_t__ status; TYPE_1__** box; int /*<<< orphan*/  boxes_left; int /*<<< orphan*/  face_bmp; } ;
struct TYPE_4__ {scalar_t__ FlagType; scalar_t__ NumMines; scalar_t__ IsMine; } ;
typedef  TYPE_2__ BOARD ;

/* Variables and functions */
 scalar_t__ COMPLETE ; 
 int /*<<< orphan*/  DEAD_BMP ; 
 scalar_t__ FLAG ; 
 scalar_t__ GAMEOVER ; 

__attribute__((used)) static void CompleteBox( BOARD *p_board, unsigned col, unsigned row )
{
    int i, j;

    if( p_board->box[col][row].FlagType != COMPLETE &&
            p_board->box[col][row].FlagType != FLAG &&
            col > 0 && col < p_board->cols + 1 &&
            row > 0 && row < p_board->rows + 1 ) {
        p_board->box[col][row].FlagType = COMPLETE;

        if( p_board->box[col][row].IsMine ) {
            p_board->face_bmp = DEAD_BMP;
            p_board->status = GAMEOVER;
        }
        else if( p_board->status != GAMEOVER )
            p_board->boxes_left--;

        if( p_board->box[col][row].NumMines == 0 )
        {
            for( i = -1; i <= 1; i++ )
            for( j = -1; j <= 1; j++ )
                CompleteBox( p_board, col + i, row + j  );
        }
    }
}