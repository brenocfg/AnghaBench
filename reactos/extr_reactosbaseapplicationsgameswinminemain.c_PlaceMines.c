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
struct TYPE_5__ {unsigned int mines; int cols; int rows; TYPE_1__** box; } ;
struct TYPE_4__ {int /*<<< orphan*/  NumMines; void* IsMine; } ;
typedef  TYPE_2__ BOARD ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int rand () ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void PlaceMines ( BOARD *p_board, int selected_col, int selected_row )
{
    int i, j;
    unsigned col, row;

    srand( (unsigned) time( NULL ) );

    /* Temporarily place a mine at the selected box until all the other
     * mines are placed, this avoids checking in the mine creation loop. */
    p_board->box[selected_col][selected_row].IsMine = TRUE;

    /* create mines */
    i = 0;
    while( (unsigned) i < p_board->mines ) {
        col = rand() % p_board->cols + 1;
        row = rand() % p_board->rows + 1;

        if( !p_board->box[col][row].IsMine ) {
            i++;
            p_board->box[col][row].IsMine = TRUE;
        }
    }

    /* Remove temporarily placed mine for selected box */
    p_board->box[selected_col][selected_row].IsMine = FALSE;

    /*
     * Now we label the remaining boxes with the
     * number of mines surrounding them.
     */
    for( col = 1; col < p_board->cols + 1; col++ )
    for( row = 1; row < p_board->rows + 1; row++ ) {
        for( i = -1; i <= 1; i++ )
        for( j = -1; j <= 1; j++ ) {
            if( p_board->box[col + i][row + j].IsMine ) {
                p_board->box[col][row].NumMines++ ;
            }
        }
    }
}