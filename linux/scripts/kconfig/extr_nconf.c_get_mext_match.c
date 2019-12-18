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
typedef  scalar_t__ match_f ;
struct TYPE_2__ {char* str; } ;

/* Variables and functions */
 scalar_t__ FIND_NEXT_MATCH_DOWN ; 
 scalar_t__ FIND_NEXT_MATCH_UP ; 
 scalar_t__ MATCH_TINKER_PATTERN_UP ; 
 int /*<<< orphan*/  current_item (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curses_menu ; 
 int item_index (int /*<<< orphan*/ ) ; 
 int items_num ; 
 TYPE_1__* k_menu_items ; 
 int /*<<< orphan*/ * strcasestr (char*,char const*) ; 

__attribute__((used)) static int get_mext_match(const char *match_str, match_f flag)
{
	int match_start = item_index(current_item(curses_menu));
	int index;

	if (flag == FIND_NEXT_MATCH_DOWN)
		++match_start;
	else if (flag == FIND_NEXT_MATCH_UP)
		--match_start;

	index = match_start;
	index = (index + items_num) % items_num;
	while (true) {
		char *str = k_menu_items[index].str;
		if (strcasestr(str, match_str) != NULL)
			return index;
		if (flag == FIND_NEXT_MATCH_UP ||
		    flag == MATCH_TINKER_PATTERN_UP)
			--index;
		else
			++index;
		index = (index + items_num) % items_num;
		if (index == match_start)
			return -1;
	}
}