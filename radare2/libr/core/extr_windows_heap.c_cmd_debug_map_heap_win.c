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
 int /*<<< orphan*/  cmd_debug_map_heap_block_win (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  help_msg ; 
 int /*<<< orphan*/  init_func () ; 
 int /*<<< orphan*/  r_core_cmd_help (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w32_list_heaps (int /*<<< orphan*/ *,char const) ; 

__attribute__((used)) static int cmd_debug_map_heap_win(RCore *core, const char *input) {
	init_func ();
	switch (input[0]) {
	case '?': // dmh?
		r_core_cmd_help (core, help_msg);
		break;
	case 'b': // dmhb
		cmd_debug_map_heap_block_win (core, input + 1);
		break;
	default:
		w32_list_heaps (core, input[0]);
		break;
	}
	return true;
}