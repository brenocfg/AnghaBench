#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  exec_path_env; } ;

/* Variables and functions */
 char const* argv_exec_path ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_1__ subcmd_config ; 

void set_argv_exec_path(const char *exec_path)
{
	argv_exec_path = exec_path;
	/*
	 * Propagate this setting to external programs.
	 */
	setenv(subcmd_config.exec_path_env, exec_path, 1);
}