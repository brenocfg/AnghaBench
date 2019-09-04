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
struct ui_browser {scalar_t__ rows; } ;
struct annotation {TYPE_1__* options; } ;
struct TYPE_2__ {scalar_t__ jump_arrows; } ;

/* Variables and functions */
 int /*<<< orphan*/  HE_COLORSET_NORMAL ; 
 int /*<<< orphan*/  __ui_browser__vline (struct ui_browser*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  annotate_browser__draw_current_jump (struct ui_browser*) ; 
 int annotation__pcnt_width (struct annotation*) ; 
 struct annotation* browser__annotation (struct ui_browser*) ; 
 int ui_browser__list_head_refresh (struct ui_browser*) ; 
 int /*<<< orphan*/  ui_browser__set_color (struct ui_browser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int annotate_browser__refresh(struct ui_browser *browser)
{
	struct annotation *notes = browser__annotation(browser);
	int ret = ui_browser__list_head_refresh(browser);
	int pcnt_width = annotation__pcnt_width(notes);

	if (notes->options->jump_arrows)
		annotate_browser__draw_current_jump(browser);

	ui_browser__set_color(browser, HE_COLORSET_NORMAL);
	__ui_browser__vline(browser, pcnt_width, 0, browser->rows - 1);
	return ret;
}