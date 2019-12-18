#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
TOOLBAR_DrawArrow (HDC hdc, INT left, INT top, COLORREF clr)
{
    INT x, y;
    HPEN hPen, hOldPen;

    if (!(hPen = CreatePen( PS_SOLID, 1, clr))) return;
    hOldPen = SelectObject ( hdc, hPen );
    x = left + 2;
    y = top;
    MoveToEx (hdc, x, y, NULL);
    LineTo (hdc, x+5, y++); x++;
    MoveToEx (hdc, x, y, NULL);
    LineTo (hdc, x+3, y++); x++;
    MoveToEx (hdc, x, y, NULL);
    LineTo (hdc, x+1, y);
    SelectObject( hdc, hOldPen );
    DeleteObject( hPen );
}