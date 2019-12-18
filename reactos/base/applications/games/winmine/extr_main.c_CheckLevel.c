#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rows; int cols; int mines; } ;
typedef  TYPE_1__ BOARD ;

/* Variables and functions */
 int BEGINNER_COLS ; 
 int BEGINNER_MINES ; 
 int BEGINNER_ROWS ; 
 int MAX_COLS ; 
 int MAX_ROWS ; 

void CheckLevel( BOARD *p_board )
{
    if( p_board->rows < BEGINNER_ROWS )
        p_board->rows = BEGINNER_ROWS;

    if( p_board->rows > MAX_ROWS )
        p_board->rows = MAX_ROWS;

    if( p_board->cols < BEGINNER_COLS )
        p_board->cols = BEGINNER_COLS;

    if( p_board->cols > MAX_COLS )
        p_board->cols = MAX_COLS;

    if( p_board->mines < BEGINNER_MINES )
        p_board->mines = BEGINNER_MINES;

    if( p_board->mines > ( p_board->cols - 1 ) * ( p_board->rows - 1 ) )
        p_board->mines = ( p_board->cols - 1 ) * ( p_board->rows - 1 );
}