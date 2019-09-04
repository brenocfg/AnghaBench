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
 size_t A_BOLD ; 
 size_t A_NORMAL ; 
 size_t A_REVERSE ; 
 size_t A_STANDOUT ; 
 size_t A_UNDERLINE ; 
 size_t COLOR_PAIR (size_t) ; 
 size_t DIALOG_BOX ; 
 size_t DIALOG_MENU_BACK ; 
 size_t DIALOG_MENU_FORE ; 
 size_t DIALOG_TEXT ; 
 size_t FUNCTION_HIGHLIGHT ; 
 size_t FUNCTION_TEXT ; 
 size_t INPUT_BOX ; 
 size_t INPUT_FIELD ; 
 size_t INPUT_HEADING ; 
 size_t INPUT_TEXT ; 
 size_t MAIN_HEADING ; 
 size_t MAIN_MENU_BACK ; 
 size_t MAIN_MENU_BOX ; 
 size_t MAIN_MENU_FORE ; 
 size_t MAIN_MENU_GREY ; 
 size_t MAIN_MENU_HEADING ; 
 size_t NORMAL ; 
 size_t SCROLLWIN_BOX ; 
 size_t SCROLLWIN_HEADING ; 
 size_t SCROLLWIN_TEXT ; 
 size_t* attributes ; 

__attribute__((used)) static void normal_color_theme(void)
{
	/* automatically add color... */
#define mkattr(name, attr) do { \
attributes[name] = attr | COLOR_PAIR(name); } while (0)
	mkattr(NORMAL, NORMAL);
	mkattr(MAIN_HEADING, A_BOLD | A_UNDERLINE);

	mkattr(MAIN_MENU_FORE, A_REVERSE);
	mkattr(MAIN_MENU_BACK, A_NORMAL);
	mkattr(MAIN_MENU_GREY, A_NORMAL);
	mkattr(MAIN_MENU_HEADING, A_BOLD);
	mkattr(MAIN_MENU_BOX, A_NORMAL);

	mkattr(SCROLLWIN_TEXT, A_NORMAL);
	mkattr(SCROLLWIN_HEADING, A_BOLD);
	mkattr(SCROLLWIN_BOX, A_BOLD);

	mkattr(DIALOG_TEXT, A_BOLD);
	mkattr(DIALOG_BOX, A_BOLD);
	mkattr(DIALOG_MENU_FORE, A_STANDOUT);
	mkattr(DIALOG_MENU_BACK, A_NORMAL);

	mkattr(INPUT_BOX, A_NORMAL);
	mkattr(INPUT_HEADING, A_BOLD);
	mkattr(INPUT_TEXT, A_NORMAL);
	mkattr(INPUT_FIELD, A_UNDERLINE);

	mkattr(FUNCTION_HIGHLIGHT, A_BOLD);
	mkattr(FUNCTION_TEXT, A_REVERSE);
}