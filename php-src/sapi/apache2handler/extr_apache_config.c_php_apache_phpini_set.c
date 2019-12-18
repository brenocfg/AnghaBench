#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ cmd_parms ;

/* Variables and functions */
 scalar_t__ ap_server_root_relative (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ apache2_php_ini_path_override ; 

__attribute__((used)) static const char *php_apache_phpini_set(cmd_parms *cmd, void *mconfig, const char *arg)
{
	if (apache2_php_ini_path_override) {
		return "Only first PHPINIDir directive honored per configuration tree - subsequent ones ignored";
	}
	apache2_php_ini_path_override = ap_server_root_relative(cmd->pool, arg);
	return NULL;
}