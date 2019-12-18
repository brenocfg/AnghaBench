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
struct TYPE_5__ {int /*<<< orphan*/  num_flags; TYPE_1__** box; int /*<<< orphan*/  IsMarkQ; } ;
struct TYPE_4__ {int FlagType; } ;
typedef  TYPE_2__ BOARD ;

/* Variables and functions */
 int COMPLETE ; 
#define  FLAG 129 
 void* NORMAL ; 
#define  QUESTION 128 

__attribute__((used)) static void AddFlag( BOARD *p_board, unsigned col, unsigned row )
{
    if( p_board->box[col][row].FlagType != COMPLETE ) {
        switch( p_board->box[col][row].FlagType ) {
        case FLAG:
            if( p_board->IsMarkQ )
                p_board->box[col][row].FlagType = QUESTION;
            else
                p_board->box[col][row].FlagType = NORMAL;
            p_board->num_flags--;
            break;

        case QUESTION:
            p_board->box[col][row].FlagType = NORMAL;
            break;

        default:
            p_board->box[col][row].FlagType = FLAG;
            p_board->num_flags++;
        }
    }
}