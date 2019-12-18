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
 int /*<<< orphan*/  R_LOG_DEBUG (char*,char*,char*) ; 
 int core_cmd_tsr2cmd (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_core_cmd_str (int /*<<< orphan*/ *,char*) ; 
 char* r_str_newf (char*,int,char const*) ; 
 int ts_node_end_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_node_named_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ts_node_start_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool handle_ts_interpret_command(RCore *core, const char *cstr, TSNode node, bool log) {
	TSNode command = ts_node_named_child (node, 0);
	ut32 command_start = ts_node_start_byte (command);
	ut32 command_end = ts_node_end_byte (command);
	char *cmd_string = r_str_newf ("%.*s", command_end - command_start, cstr + command_start);
	char *str = r_core_cmd_str (core, cmd_string);
	R_LOG_DEBUG ("interpret_command cmd_string = '%s', result to interpret = '%s'\n", cmd_string, str);
	free (cmd_string);
	bool res = core_cmd_tsr2cmd (core, str, log);
	free (str);
	return res;
}