#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut32 ;
struct TYPE_3__ {int /*<<< orphan*/  rcmd; } ;
typedef  int /*<<< orphan*/  TSNode ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_LOG_DEBUG (char*,int,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int r_cmd_call (int /*<<< orphan*/ ,char*) ; 
 char* r_str_newf (char*,int,char const*) ; 
 int ts_node_child_count (int /*<<< orphan*/ ) ; 
 int ts_node_end_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_node_named_child (int /*<<< orphan*/ ,int) ; 
 int ts_node_start_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool handle_ts_arged_command(RCore *core, const char *cstr, TSNode node) {
	TSNode command = ts_node_named_child (node, 0);
	ut32 cmd_start_byte = ts_node_start_byte (command);
	ut32 cmd_end_byte = ts_node_end_byte (command);
	R_LOG_DEBUG ("command: '%.*s'\n", cmd_end_byte - cmd_start_byte, cstr + cmd_start_byte);

	ut32 child_count = ts_node_child_count (node);
	ut32 last_end_byte = cmd_end_byte;
	int i;
	for (i = 1; i < child_count; ++i) {
		TSNode arg = ts_node_named_child (node, i);
		ut32 start_byte = ts_node_start_byte (arg);
		ut32 end_byte = ts_node_end_byte (arg);
		if (last_end_byte < end_byte) {
			last_end_byte = end_byte;
		}
		R_LOG_DEBUG ("arg: '%.*s'\n", end_byte - start_byte, cstr + start_byte);
	}
	char *cmd_string = r_str_newf ("%.*s", last_end_byte - cmd_start_byte, cstr + cmd_start_byte);
	bool res = r_cmd_call (core->rcmd, cmd_string) != -1;
	free (cmd_string);
	return res;
}