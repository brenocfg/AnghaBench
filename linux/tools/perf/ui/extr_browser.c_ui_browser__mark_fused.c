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
struct ui_browser {unsigned int top_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLSMG_LTEE_CHAR ; 
 int /*<<< orphan*/  SLSMG_ULCORN_CHAR ; 
 int /*<<< orphan*/  SLsmg_draw_hline (int) ; 
 int /*<<< orphan*/  SLsmg_set_char_set (int) ; 
 int /*<<< orphan*/  SLsmg_write_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_browser__gotorc (struct ui_browser*,unsigned int,unsigned int) ; 

void ui_browser__mark_fused(struct ui_browser *browser, unsigned int column,
			    unsigned int row, bool arrow_down)
{
	unsigned int end_row;

	if (row >= browser->top_idx)
		end_row = row - browser->top_idx;
	else
		return;

	SLsmg_set_char_set(1);

	if (arrow_down) {
		ui_browser__gotorc(browser, end_row, column - 1);
		SLsmg_write_char(SLSMG_ULCORN_CHAR);
		ui_browser__gotorc(browser, end_row, column);
		SLsmg_draw_hline(2);
		ui_browser__gotorc(browser, end_row + 1, column - 1);
		SLsmg_write_char(SLSMG_LTEE_CHAR);
	} else {
		ui_browser__gotorc(browser, end_row, column - 1);
		SLsmg_write_char(SLSMG_LTEE_CHAR);
		ui_browser__gotorc(browser, end_row, column);
		SLsmg_draw_hline(2);
	}

	SLsmg_set_char_set(0);
}