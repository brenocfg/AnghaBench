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
 int /*<<< orphan*/  R2_HOME_DATADIR ; 
 int /*<<< orphan*/  R_JOIN_2_PATHS (int /*<<< orphan*/ ,char*) ; 
 char* r_str_home (int /*<<< orphan*/ ) ; 

char *__get_panels_config_dir_path() {
	return r_str_home (R_JOIN_2_PATHS (R2_HOME_DATADIR, ".r2panels"));
}