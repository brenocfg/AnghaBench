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

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  COLOR_RED ; 
 int /*<<< orphan*/  COLOR_WHITE ; 
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int /*<<< orphan*/  DLG_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  border ; 
 int /*<<< orphan*/  button_active ; 
 int /*<<< orphan*/  button_inactive ; 
 int /*<<< orphan*/  button_key_active ; 
 int /*<<< orphan*/  button_key_inactive ; 
 int /*<<< orphan*/  button_label_active ; 
 int /*<<< orphan*/  button_label_inactive ; 
 int /*<<< orphan*/  check ; 
 int /*<<< orphan*/  check_selected ; 
 int /*<<< orphan*/  darrow ; 
 int /*<<< orphan*/  dialog ; 
 int /*<<< orphan*/  inputbox ; 
 int /*<<< orphan*/  inputbox_border ; 
 int /*<<< orphan*/  item ; 
 int /*<<< orphan*/  item_selected ; 
 int /*<<< orphan*/  menubox ; 
 int /*<<< orphan*/  menubox_border ; 
 int /*<<< orphan*/  position_indicator ; 
 int /*<<< orphan*/  screen ; 
 int /*<<< orphan*/  searchbox ; 
 int /*<<< orphan*/  searchbox_border ; 
 int /*<<< orphan*/  searchbox_title ; 
 int /*<<< orphan*/  shadow ; 
 int /*<<< orphan*/  tag ; 
 int /*<<< orphan*/  tag_key ; 
 int /*<<< orphan*/  tag_key_selected ; 
 int /*<<< orphan*/  tag_selected ; 
 int /*<<< orphan*/  title ; 
 int /*<<< orphan*/  uarrow ; 

__attribute__((used)) static void set_blackbg_theme(void)
{
	DLG_COLOR(screen, COLOR_RED,   COLOR_BLACK, true);
	DLG_COLOR(shadow, COLOR_BLACK, COLOR_BLACK, false);
	DLG_COLOR(dialog, COLOR_WHITE, COLOR_BLACK, false);
	DLG_COLOR(title,  COLOR_RED,   COLOR_BLACK, false);
	DLG_COLOR(border, COLOR_BLACK, COLOR_BLACK, true);

	DLG_COLOR(button_active,         COLOR_YELLOW, COLOR_RED,   false);
	DLG_COLOR(button_inactive,       COLOR_YELLOW, COLOR_BLACK, false);
	DLG_COLOR(button_key_active,     COLOR_YELLOW, COLOR_RED,   true);
	DLG_COLOR(button_key_inactive,   COLOR_RED,    COLOR_BLACK, false);
	DLG_COLOR(button_label_active,   COLOR_WHITE,  COLOR_RED,   false);
	DLG_COLOR(button_label_inactive, COLOR_BLACK,  COLOR_BLACK, true);

	DLG_COLOR(inputbox,         COLOR_YELLOW, COLOR_BLACK, false);
	DLG_COLOR(inputbox_border,  COLOR_YELLOW, COLOR_BLACK, false);

	DLG_COLOR(searchbox,        COLOR_YELLOW, COLOR_BLACK, false);
	DLG_COLOR(searchbox_title,  COLOR_YELLOW, COLOR_BLACK, true);
	DLG_COLOR(searchbox_border, COLOR_BLACK,  COLOR_BLACK, true);

	DLG_COLOR(position_indicator, COLOR_RED, COLOR_BLACK,  false);

	DLG_COLOR(menubox,          COLOR_YELLOW, COLOR_BLACK, false);
	DLG_COLOR(menubox_border,   COLOR_BLACK,  COLOR_BLACK, true);

	DLG_COLOR(item,             COLOR_WHITE, COLOR_BLACK, false);
	DLG_COLOR(item_selected,    COLOR_WHITE, COLOR_RED,   false);

	DLG_COLOR(tag,              COLOR_RED,    COLOR_BLACK, false);
	DLG_COLOR(tag_selected,     COLOR_YELLOW, COLOR_RED,   true);
	DLG_COLOR(tag_key,          COLOR_RED,    COLOR_BLACK, false);
	DLG_COLOR(tag_key_selected, COLOR_YELLOW, COLOR_RED,   true);

	DLG_COLOR(check,            COLOR_YELLOW, COLOR_BLACK, false);
	DLG_COLOR(check_selected,   COLOR_YELLOW, COLOR_RED,   true);

	DLG_COLOR(uarrow, COLOR_RED, COLOR_BLACK, false);
	DLG_COLOR(darrow, COLOR_RED, COLOR_BLACK, false);
}