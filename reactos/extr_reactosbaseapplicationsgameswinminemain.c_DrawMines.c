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
struct TYPE_4__ {unsigned int rows; unsigned int cols; int /*<<< orphan*/  hMinesBMP; } ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_1__ BOARD ;

/* Variables and functions */
 int /*<<< orphan*/  DrawMine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DrawMines ( HDC hdc, HDC hMemDC, BOARD *p_board )
{
    HGDIOBJ hOldObj;
    unsigned col, row;
    hOldObj = SelectObject (hMemDC, p_board->hMinesBMP);

    for( row = 1; row <= p_board->rows; row++ ) {
      for( col = 1; col <= p_board->cols; col++ ) {
        DrawMine( hdc, hMemDC, p_board, col, row, FALSE );
      }
    }
    SelectObject( hMemDC, hOldObj );
}