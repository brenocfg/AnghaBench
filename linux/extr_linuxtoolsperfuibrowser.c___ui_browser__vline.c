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
typedef  scalar_t__ u16 ;
struct ui_browser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLsmg_draw_vline (scalar_t__) ; 
 int /*<<< orphan*/  SLsmg_set_char_set (int) ; 
 int /*<<< orphan*/  ui_browser__gotorc (struct ui_browser*,scalar_t__,unsigned int) ; 

void __ui_browser__vline(struct ui_browser *browser, unsigned int column,
			 u16 start, u16 end)
{
	SLsmg_set_char_set(1);
	ui_browser__gotorc(browser, start, column);
	SLsmg_draw_vline(end - start + 1);
	SLsmg_set_char_set(0);
}