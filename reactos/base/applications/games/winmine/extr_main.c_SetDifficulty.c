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
struct TYPE_3__ {int difficulty; int /*<<< orphan*/  mines; int /*<<< orphan*/  rows; int /*<<< orphan*/  cols; int /*<<< orphan*/  hWnd; int /*<<< orphan*/  hInst; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int DIFFICULTY ;
typedef  TYPE_1__ BOARD ;

/* Variables and functions */
#define  ADVANCED 131 
 int /*<<< orphan*/  ADVANCED_COLS ; 
 int /*<<< orphan*/  ADVANCED_MINES ; 
 int /*<<< orphan*/  ADVANCED_ROWS ; 
#define  BEGINNER 130 
 int /*<<< orphan*/  BEGINNER_COLS ; 
 int /*<<< orphan*/  BEGINNER_MINES ; 
 int /*<<< orphan*/  BEGINNER_ROWS ; 
#define  CUSTOM 129 
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CustomDlgProc ; 
 int /*<<< orphan*/  DLG_CUSTOM ; 
 scalar_t__ DialogBoxParamW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  EXPERT 128 
 int /*<<< orphan*/  EXPERT_COLS ; 
 int /*<<< orphan*/  EXPERT_MINES ; 
 int /*<<< orphan*/  EXPERT_ROWS ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int IDM_BEGINNER ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MF_CHECKED ; 
 int /*<<< orphan*/  MF_UNCHECKED ; 

__attribute__((used)) static void SetDifficulty( BOARD *p_board, DIFFICULTY difficulty )
{
    HMENU hMenu;

    if ( difficulty == CUSTOM )
        if (DialogBoxParamW( p_board->hInst, MAKEINTRESOURCEW(DLG_CUSTOM), p_board->hWnd,
                    CustomDlgProc, (LPARAM) p_board) != 0)
           return;

    hMenu = GetMenu( p_board->hWnd );
    CheckMenuItem( hMenu, IDM_BEGINNER + p_board->difficulty, MF_UNCHECKED );
    p_board->difficulty = difficulty;
    CheckMenuItem( hMenu, IDM_BEGINNER + difficulty, MF_CHECKED );

    switch( difficulty ) {
    case BEGINNER:
        p_board->cols = BEGINNER_COLS;
        p_board->rows = BEGINNER_ROWS;
        p_board->mines = BEGINNER_MINES;
        break;

    case ADVANCED:
        p_board->cols = ADVANCED_COLS;
        p_board->rows = ADVANCED_ROWS;
        p_board->mines = ADVANCED_MINES;
        break;

    case EXPERT:
        p_board->cols = EXPERT_COLS;
        p_board->rows = EXPERT_ROWS;

        p_board->mines = EXPERT_MINES;
        break;

    case CUSTOM:
        break;
    }
}