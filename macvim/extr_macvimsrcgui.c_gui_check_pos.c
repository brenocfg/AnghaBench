#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ row; scalar_t__ col; scalar_t__ cursor_row; scalar_t__ cursor_col; int /*<<< orphan*/  cursor_is_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__ gui ; 
 scalar_t__ screen_Columns ; 
 scalar_t__ screen_Rows ; 

__attribute__((used)) static void
gui_check_pos()
{
    if (gui.row >= screen_Rows)
	gui.row = screen_Rows - 1;
    if (gui.col >= screen_Columns)
	gui.col = screen_Columns - 1;
    if (gui.cursor_row >= screen_Rows || gui.cursor_col >= screen_Columns)
	gui.cursor_is_valid = FALSE;
}