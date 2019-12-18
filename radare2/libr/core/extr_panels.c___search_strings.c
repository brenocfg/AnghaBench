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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 char* PANEL_TITLE_STRINGS_BIN ; 
 char* PANEL_TITLE_STRINGS_DATA ; 
 char* __search_db (int /*<<< orphan*/ *,char const*) ; 
 char* __show_status_input (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_str_newf (char*,char*,char const*) ; 

char *__search_strings (RCore *core, bool whole) {
	const char *title = whole ? PANEL_TITLE_STRINGS_BIN : PANEL_TITLE_STRINGS_DATA;
	const char *str = __show_status_input (core, "Search Strings: ");
	char *db_val = __search_db (core, title);
	char *ret = r_str_newf ("%s~%s", db_val, str);
	free (db_val);
	return ret;
}