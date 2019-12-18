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
 int /*<<< orphan*/  help_msg_env ; 
 int /*<<< orphan*/  help_msg_percent ; 
 int /*<<< orphan*/  r_core_cmd_help (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_help_percent(RCore *core) {
	r_core_cmd_help (core, help_msg_percent);
	r_core_cmd_help (core, help_msg_env);
}