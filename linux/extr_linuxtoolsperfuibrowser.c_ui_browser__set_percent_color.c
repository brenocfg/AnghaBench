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
struct ui_browser {int dummy; } ;

/* Variables and functions */
 int ui_browser__percent_color (struct ui_browser*,double,int) ; 
 int /*<<< orphan*/  ui_browser__set_color (struct ui_browser*,int) ; 

void ui_browser__set_percent_color(struct ui_browser *browser,
				   double percent, bool current)
{
	 int color = ui_browser__percent_color(browser, percent, current);
	 ui_browser__set_color(browser, color);
}