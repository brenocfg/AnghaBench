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
 int /*<<< orphan*/  r_cons_printf (char*) ; 
 int r_core_run_script (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int cmd_stdin(void *data, const char *input) {
	RCore *core = (RCore *)data;
	if (input[0] == '?') {
		r_cons_printf ("Usage: '-' '.-' '. -' do the same\n");
		return false;
	}
	return r_core_run_script (core, "-");
}