#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ top; scalar_t__ left; } ;
struct TYPE_7__ {unsigned int cols; unsigned int rows; scalar_t__ status; TYPE_2__ mines_rect; TYPE_1__** box; } ;
struct TYPE_5__ {int FlagType; scalar_t__ NumMines; scalar_t__ IsMine; } ;
typedef  unsigned int MINEBMP_OFFSET ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_3__ BOARD ;

/* Variables and functions */
 unsigned int BOX_BMP ; 
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
#define  COMPLETE 131 
 unsigned int EXPLODE_BMP ; 
#define  FLAG 130 
 unsigned int FLAG_BMP ; 
 scalar_t__ GAMEOVER ; 
 unsigned int MINE_BMP ; 
 unsigned int MINE_HEIGHT ; 
 unsigned int MINE_WIDTH ; 
 unsigned int MPRESS_BMP ; 
#define  NORMAL 129 
 unsigned int QPRESS_BMP ; 
#define  QUESTION 128 
 unsigned int QUESTION_BMP ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  WINE_TRACE (char*) ; 
 unsigned int WRONG_BMP ; 

__attribute__((used)) static void DrawMine( HDC hdc, HDC hMemDC, BOARD *p_board, unsigned col, unsigned row, BOOL IsPressed )
{
    MINEBMP_OFFSET offset = BOX_BMP;

    if( col == 0 || col > p_board->cols || row == 0 || row > p_board->rows )
           return;

    if( p_board->status == GAMEOVER ) {
        if( p_board->box[col][row].IsMine ) {
            switch( p_board->box[col][row].FlagType ) {
            case FLAG:
                offset = FLAG_BMP;
                break;
            case COMPLETE:
                offset = EXPLODE_BMP;
                break;
            case QUESTION:
                /* fall through */
            case NORMAL:
                offset = MINE_BMP;
            }
        } else {
            switch( p_board->box[col][row].FlagType ) {
            case QUESTION:
                offset = QUESTION_BMP;
                break;
            case FLAG:
                offset = WRONG_BMP;
                break;
            case NORMAL:
                offset = BOX_BMP;
                break;
            case COMPLETE:
                /* Do nothing */
                break;
            default:
                WINE_TRACE("Unknown FlagType during game over in DrawMine\n");
                break;
            }
        }
    } else {    /* WAITING or PLAYING */
        switch( p_board->box[col][row].FlagType ) {
        case QUESTION:
            if( !IsPressed )
                offset = QUESTION_BMP;
            else
                offset = QPRESS_BMP;
            break;
        case FLAG:
            offset = FLAG_BMP;
            break;
        case NORMAL:
            if( !IsPressed )
                offset = BOX_BMP;
            else
                offset = MPRESS_BMP;
            break;
        case COMPLETE:
            /* Do nothing */
            break;
        default:
            WINE_TRACE("Unknown FlagType while playing in DrawMine\n");
            break;
        }
    }

    if( p_board->box[col][row].FlagType == COMPLETE
        && !p_board->box[col][row].IsMine )
          offset = (MINEBMP_OFFSET) p_board->box[col][row].NumMines;

    BitBlt( hdc,
            (col - 1) * MINE_WIDTH + p_board->mines_rect.left,
            (row - 1) * MINE_HEIGHT + p_board->mines_rect.top,
            MINE_WIDTH, MINE_HEIGHT,
            hMemDC, 0, offset * MINE_HEIGHT, SRCCOPY );
}