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
struct TYPE_2__ {char const* exec_name; char const* prefix; char const* exec_path; char const* exec_path_env; } ;

/* Variables and functions */
 TYPE_1__ subcmd_config ; 

void exec_cmd_init(const char *exec_name, const char *prefix,
		   const char *exec_path, const char *exec_path_env)
{
	subcmd_config.exec_name		= exec_name;
	subcmd_config.prefix		= prefix;
	subcmd_config.exec_path		= exec_path;
	subcmd_config.exec_path_env	= exec_path_env;
}