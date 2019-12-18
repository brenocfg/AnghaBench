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

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int ddebug_dyndbg_param_cb (char*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpr_info (char*,char const*,char*,char*) ; 

int ddebug_dyndbg_module_param_cb(char *param, char *val, const char *module)
{
	vpr_info("module: %s %s=\"%s\"\n", module, param, val);
	return ddebug_dyndbg_param_cb(param, val, module, -ENOENT);
}