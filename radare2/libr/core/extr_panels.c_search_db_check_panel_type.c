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
typedef  int /*<<< orphan*/  RPanel ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 scalar_t__ __check_panel_type (int /*<<< orphan*/ *,char*) ; 
 char* __search_db (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 

bool search_db_check_panel_type (RCore *core, RPanel *panel, const char *ch) {
	char *str = __search_db (core, ch);
	bool ret = str && __check_panel_type (panel, str);
	free (str);
	return ret;
}