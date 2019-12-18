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
typedef  int /*<<< orphan*/  TSNode ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int handle_ts_arged_command (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int handle_ts_interpret_command (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int handle_ts_tmp_seek_command (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_ts_arged_command (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ts_interpret_command (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ts_tmp_seek_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_line_hist_add (char const*) ; 
 int /*<<< orphan*/  run_pending_anal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool handle_ts_command(RCore *core, const char *cstr, TSNode node, bool log) {
	bool ret = false;

	if (log) {
		r_line_hist_add (cstr);
	}
	if (is_ts_arged_command (node)) {
		ret = handle_ts_arged_command (core, cstr, node);
	} else if (is_ts_tmp_seek_command (node)) {
		ret = handle_ts_tmp_seek_command (core, cstr, node, log);
	} else if (is_ts_interpret_command (node)) {
		ret = handle_ts_interpret_command (core, cstr, node, log);
	}
	/* run pending analysis commands */
	run_pending_anal (core);
	return ret;
}