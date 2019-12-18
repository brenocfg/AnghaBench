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
 int /*<<< orphan*/  COLOR_BLUE ; 
 int /*<<< orphan*/  COLOR_WHITE ; 
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int /*<<< orphan*/  DLG_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  button_key_active ; 
 int /*<<< orphan*/  button_label_active ; 
 int /*<<< orphan*/  position_indicator ; 
 int /*<<< orphan*/  searchbox_title ; 
 int /*<<< orphan*/  set_classic_theme () ; 
 int /*<<< orphan*/  tag ; 
 int /*<<< orphan*/  tag_key ; 
 int /*<<< orphan*/  title ; 

__attribute__((used)) static void set_bluetitle_theme(void)
{
	set_classic_theme();
	DLG_COLOR(title,               COLOR_BLUE,   COLOR_WHITE, true);
	DLG_COLOR(button_key_active,   COLOR_YELLOW, COLOR_BLUE,  true);
	DLG_COLOR(button_label_active, COLOR_WHITE,  COLOR_BLUE,  true);
	DLG_COLOR(searchbox_title,     COLOR_BLUE,   COLOR_WHITE, true);
	DLG_COLOR(position_indicator,  COLOR_BLUE,   COLOR_WHITE, true);
	DLG_COLOR(tag,                 COLOR_BLUE,   COLOR_WHITE, true);
	DLG_COLOR(tag_key,             COLOR_BLUE,   COLOR_WHITE, true);

}