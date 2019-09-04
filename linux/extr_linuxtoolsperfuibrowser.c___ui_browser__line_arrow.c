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
typedef  scalar_t__ u64 ;
struct ui_browser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ui_browser__line_arrow_down (struct ui_browser*,unsigned int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __ui_browser__line_arrow_up (struct ui_browser*,unsigned int,scalar_t__,scalar_t__) ; 

void __ui_browser__line_arrow(struct ui_browser *browser, unsigned int column,
			      u64 start, u64 end)
{
	if (start > end)
		__ui_browser__line_arrow_up(browser, column, start, end);
	else
		__ui_browser__line_arrow_down(browser, column, start, end);
}