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
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_config_get (int /*<<< orphan*/ ,char*) ; 
 char* r_file_abspath (int /*<<< orphan*/ ) ; 
 int r_sys_mkdirp (char*) ; 

__attribute__((used)) static int projectInit(RCore *core) {
	char *prjdir = r_file_abspath (r_config_get (core->config, "dir.projects"));
	int ret = r_sys_mkdirp (prjdir);
	if (!ret) {
		eprintf ("Cannot mkdir dir.projects\n");
	}
	free (prjdir);
	return ret;
}