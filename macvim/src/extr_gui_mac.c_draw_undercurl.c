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

/* Variables and functions */
 int FILL_X (int) ; 
 int FILL_Y (int) ; 
 int /*<<< orphan*/  LineTo (int,int) ; 
 int /*<<< orphan*/  MoveTo (int,int) ; 
 int /*<<< orphan*/  RGBForeColor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  specialColor ; 

__attribute__((used)) static void
draw_undercurl(int flags, int row, int col, int cells)
{
    int			x;
    int			offset;
    const static int	val[8] = {1, 0, 0, 0, 1, 2, 2, 2 };
    int			y = FILL_Y(row + 1) - 1;

    RGBForeColor(&specialColor);

    offset = val[FILL_X(col) % 8];
    MoveTo(FILL_X(col), y - offset);

    for (x = FILL_X(col); x < FILL_X(col + cells); ++x)
    {
	offset = val[x % 8];
	LineTo(x, y - offset);
    }
}