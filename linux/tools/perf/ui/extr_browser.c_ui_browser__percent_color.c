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
struct ui_browser {scalar_t__ navkeypressed; int /*<<< orphan*/  use_navkeypressed; } ;

/* Variables and functions */
 int HE_COLORSET_MEDIUM ; 
 int HE_COLORSET_NORMAL ; 
 int HE_COLORSET_SELECTED ; 
 int HE_COLORSET_TOP ; 
 double MIN_GREEN ; 
 double MIN_RED ; 

__attribute__((used)) static int ui_browser__percent_color(struct ui_browser *browser,
				     double percent, bool current)
{
	if (current && (!browser->use_navkeypressed || browser->navkeypressed))
		return HE_COLORSET_SELECTED;
	if (percent >= MIN_RED)
		return HE_COLORSET_TOP;
	if (percent >= MIN_GREEN)
		return HE_COLORSET_MEDIUM;
	return HE_COLORSET_NORMAL;
}