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
struct TYPE_3__ {int fixedarch; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool set_tmp_arch(RCore *core, char *arch, char **tmparch) {
	if (!tmparch) {
		eprintf ("tmparch should be set\n");
	}
	*tmparch = strdup (r_config_get (core->config, "asm.arch"));
	r_config_set (core->config, "asm.arch", arch);
	core->fixedarch = true;
	return true;
}