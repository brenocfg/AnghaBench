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
typedef  int /*<<< orphan*/  TSTree ;
typedef  int /*<<< orphan*/  TSParser ;
typedef  int /*<<< orphan*/  TSNode ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int handle_ts_commands (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_ts_commands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  tree_sitter_r2cmd () ; 
 int /*<<< orphan*/  ts_node_has_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_parser_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_parser_new () ; 
 int /*<<< orphan*/ * ts_parser_parse_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_parser_set_language (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_tree_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_tree_root_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool core_cmd_tsr2cmd(RCore *core, const char *cstr, bool log) {
	TSParser *parser = ts_parser_new ();

	ts_parser_set_language (parser, tree_sitter_r2cmd ());

	TSTree *tree = ts_parser_parse_string (parser, NULL, cstr, strlen (cstr));
	TSNode root = ts_tree_root_node (tree);
	bool res = false;
	if (is_ts_commands (root) && !ts_node_has_error (root)) {
		res = handle_ts_commands (core, cstr, root, log);
	} else {
		eprintf ("Error while parsing command: `%s`\n", cstr);
	}

	ts_tree_delete (tree);
	ts_parser_delete (parser);
	return res;
}