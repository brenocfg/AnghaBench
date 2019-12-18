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
struct TYPE_4__ {int /*<<< orphan*/  hWnd; int /*<<< orphan*/  hMinesBMP; } ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_1__ BOARD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawMine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void UnpressBox( BOARD *p_board, unsigned col, unsigned row )
{
    HDC hdc;
    HGDIOBJ hOldObj;
    HDC hMemDC;

    hdc = GetDC( p_board->hWnd );
    hMemDC = CreateCompatibleDC( hdc );
    hOldObj = SelectObject( hMemDC, p_board->hMinesBMP );

    DrawMine( hdc, hMemDC, p_board, col, row, FALSE );

    SelectObject( hMemDC, hOldObj );
    DeleteDC( hMemDC );
    ReleaseDC( p_board->hWnd, hdc );
}