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
struct ui_browser {scalar_t__ x; scalar_t__ y; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLsmg_gotorc (scalar_t__,scalar_t__) ; 

void ui_browser__gotorc_title(struct ui_browser *browser, int y, int x)
{
	SLsmg_gotorc(browser->y + y, browser->x + x);
}