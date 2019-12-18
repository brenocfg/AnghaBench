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
struct ui_browser {int /*<<< orphan*/  title; } ;

/* Variables and functions */
 int /*<<< orphan*/  ui__refresh_dimensions (int) ; 
 int /*<<< orphan*/  ui_browser__refresh (struct ui_browser*) ; 
 int /*<<< orphan*/  ui_browser__show (struct ui_browser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_helpline__current ; 

void ui_browser__handle_resize(struct ui_browser *browser)
{
	ui__refresh_dimensions(false);
	ui_browser__show(browser, browser->title, ui_helpline__current);
	ui_browser__refresh(browser);
}