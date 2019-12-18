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
 int /*<<< orphan*/  frame_comp_pos (int /*<<< orphan*/ ,int*,int*) ; 
 int tabline_height () ; 
 int /*<<< orphan*/  topframe ; 

int
win_comp_pos()
{
    int		row = tabline_height();
    int		col = 0;

    frame_comp_pos(topframe, &row, &col);
    return row;
}