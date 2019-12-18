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
struct ui_browser {int y; scalar_t__ x; scalar_t__ extra_title_lines; scalar_t__ rows; scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 scalar_t__ SLtt_Screen_Cols ; 
 scalar_t__ SLtt_Screen_Rows ; 

void ui_browser__refresh_dimensions(struct ui_browser *browser)
{
	browser->width = SLtt_Screen_Cols - 1;
	browser->height = browser->rows = SLtt_Screen_Rows - 2;
	browser->rows -= browser->extra_title_lines;
	browser->y = 1;
	browser->x = 0;
}