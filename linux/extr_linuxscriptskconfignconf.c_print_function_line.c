#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  func; int /*<<< orphan*/  key_str; } ;

/* Variables and functions */
 size_t FUNCTION_HIGHLIGHT ; 
 size_t FUNCTION_TEXT ; 
 size_t NORMAL ; 
 int /*<<< orphan*/ * attributes ; 
 TYPE_1__* function_keys ; 
 int function_keys_num ; 
 int getmaxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_window ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdscr ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_function_line(void)
{
	int i;
	int offset = 1;
	const int skip = 1;
	int lines = getmaxy(stdscr);

	for (i = 0; i < function_keys_num; i++) {
		(void) wattrset(main_window, attributes[FUNCTION_HIGHLIGHT]);
		mvwprintw(main_window, lines-3, offset,
				"%s",
				function_keys[i].key_str);
		(void) wattrset(main_window, attributes[FUNCTION_TEXT]);
		offset += strlen(function_keys[i].key_str);
		mvwprintw(main_window, lines-3,
				offset, "%s",
				function_keys[i].func);
		offset += strlen(function_keys[i].func) + skip;
	}
	(void) wattrset(main_window, attributes[NORMAL]);
}