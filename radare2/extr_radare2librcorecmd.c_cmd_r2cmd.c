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
 scalar_t__ r_str_startswith (char const*,char const*) ; 
 int /*<<< orphan*/  r_sys_cmdf (char*,char const*) ; 

__attribute__((used)) static int cmd_r2cmd(RCore *core, const char *input) {
	const char *r2cmds[] = {
		"rax2", "r2pm", "rasm2", "rabin2", "rahash2", "rafind2", "rarun2", "ragg2",
		NULL
	};
	int i;
	for (i = 0; r2cmds[i]; i++) {
		if (r_str_startswith (input, r2cmds[i])) {
			r_sys_cmdf ("r%s", input);
			return true;
		}
	}
	return false;
}