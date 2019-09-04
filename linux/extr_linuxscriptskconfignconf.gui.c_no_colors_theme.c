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
 int A_BOLD ; 
 int A_NORMAL ; 
 int A_REVERSE ; 
 int A_STANDOUT ; 
 int A_UNDERLINE ; 
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
 int* attributes ; 

__attribute__((used)) static void no_colors_theme(void)
{
	/* automatically add highlight, no color */
#define mkattrn(name, attr) { attributes[name] = attr; }

	mkattrn(NORMAL, NORMAL);
	mkattrn(MAIN_HEADING, A_BOLD | A_UNDERLINE);

	mkattrn(MAIN_MENU_FORE, A_STANDOUT);
	mkattrn(MAIN_MENU_BACK, A_NORMAL);
	mkattrn(MAIN_MENU_GREY, A_NORMAL);
	mkattrn(MAIN_MENU_HEADING, A_BOLD);
	mkattrn(MAIN_MENU_BOX, A_NORMAL);

	mkattrn(SCROLLWIN_TEXT, A_NORMAL);
	mkattrn(SCROLLWIN_HEADING, A_BOLD);
	mkattrn(SCROLLWIN_BOX, A_BOLD);

	mkattrn(DIALOG_TEXT, A_NORMAL);
	mkattrn(DIALOG_BOX, A_BOLD);
	mkattrn(DIALOG_MENU_FORE, A_STANDOUT);
	mkattrn(DIALOG_MENU_BACK, A_NORMAL);

	mkattrn(INPUT_BOX, A_BOLD);
	mkattrn(INPUT_HEADING, A_BOLD);
	mkattrn(INPUT_TEXT, A_NORMAL);
	mkattrn(INPUT_FIELD, A_UNDERLINE);

	mkattrn(FUNCTION_HIGHLIGHT, A_BOLD);
	mkattrn(FUNCTION_TEXT, A_REVERSE);
}