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
typedef  int ut32 ;
typedef  int /*<<< orphan*/  TSNode ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_LOG_DEBUG (char*,int) ; 
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int handle_ts_command (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_node_named_child (int /*<<< orphan*/ ,int) ; 
 int ts_node_named_child_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool handle_ts_commands(RCore *core, const char *cstr, TSNode node, bool log) {
	ut32 child_count = ts_node_named_child_count (node);
	bool res = true;
	int i;

	R_LOG_DEBUG ("commands with %d childs\n", child_count);
	for (i = 0; i < child_count; ++i) {
		TSNode command = ts_node_named_child (node, i);
		res &= handle_ts_command (core, cstr, command, log);
		if (!res) {
			eprintf ("Error while parsing command: %s\n", cstr);
			return false;
		}
	}
	return res;
}