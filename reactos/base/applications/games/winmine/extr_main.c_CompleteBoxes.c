#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__** box; } ;
struct TYPE_5__ {scalar_t__ FlagType; unsigned int NumMines; } ;
typedef  TYPE_2__ BOARD ;

/* Variables and functions */
 scalar_t__ COMPLETE ; 
 int /*<<< orphan*/  CompleteBox (TYPE_2__*,unsigned int,unsigned int) ; 
 scalar_t__ FLAG ; 

__attribute__((used)) static void CompleteBoxes( BOARD *p_board, unsigned col, unsigned row )
{
    unsigned numFlags = 0;
    int i, j;

    if( p_board->box[col][row].FlagType == COMPLETE ) {
        for( i = -1; i <= 1; i++ )
          for( j = -1; j <= 1; j++ ) {
            if( p_board->box[col+i][row+j].FlagType == FLAG )
                numFlags++;
          }

        if( numFlags == p_board->box[col][row].NumMines ) {
            for( i = -1; i <= 1; i++ )
              for( j = -1; j <= 1; j++ ) {
                if( p_board->box[col+i][row+j].FlagType != FLAG )
                    CompleteBox( p_board, col+i, row+j );
              }
        }
    }
}