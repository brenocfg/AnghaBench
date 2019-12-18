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
 int /*<<< orphan*/  cmd_help_percent (int /*<<< orphan*/ *) ; 
 int r_core_cmdf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int cmd_env(void *data, const char *input) {
	RCore *core = (RCore*)data;
	int ret = true;
	switch (*input) {
	case '?':
		cmd_help_percent (core);
		break;
	default:
		ret = r_core_cmdf (core, "env %s", input);
	}
	return ret;
}