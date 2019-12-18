#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int ut32 ;
struct TYPE_5__ {int /*<<< orphan*/  num; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  TSNode ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_LOG_DEBUG (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int handle_ts_command (TYPE_1__*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_num_math (int /*<<< orphan*/ ,char*) ; 
 char* r_str_newf (char*,int,char const*) ; 
 int ts_node_end_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_node_named_child (int /*<<< orphan*/ ,int) ; 
 int ts_node_start_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool handle_ts_tmp_seek_command(RCore *core, const char *cstr, TSNode node, bool log) {
	TSNode command = ts_node_named_child (node, 0);
	TSNode offset = ts_node_named_child (node, 1);
	ut32 offset_start = ts_node_start_byte (offset);
	ut32 offset_end = ts_node_end_byte (offset);
	char *offset_string = r_str_newf ("%.*s", offset_end - offset_start, cstr + offset_start);
	ut64 orig_offset = core->offset;
	R_LOG_DEBUG ("tmp_seek command, command X on tmp_seek %s\n", offset_string);
	r_core_seek (core, r_num_math (core->num, offset_string), 1);
	bool res = handle_ts_command (core, cstr, command, log);
	r_core_seek (core, orig_offset, 1);
	free (offset_string);
	return res;
}