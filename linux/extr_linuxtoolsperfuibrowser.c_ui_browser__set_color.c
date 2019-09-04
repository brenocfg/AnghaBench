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
struct ui_browser {int current_color; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLsmg_set_color (int) ; 

int ui_browser__set_color(struct ui_browser *browser, int color)
{
	int ret = browser->current_color;
	browser->current_color = color;
	SLsmg_set_color(color);
	return ret;
}