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
 int /*<<< orphan*/  R2_HOME_BIN ; 
 int /*<<< orphan*/  R_SYS_ENVSEP ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_str_home (int /*<<< orphan*/ ) ; 
 char* r_str_newf (char*,char*,int /*<<< orphan*/ ,char*) ; 
 char* r_sys_getenv (char*) ; 
 int /*<<< orphan*/  r_sys_setenv (char*,char*) ; 

__attribute__((used)) static void r_core_setenv (RCore *core) {
	char *e = r_sys_getenv ("PATH");
	char *h = r_str_home (R2_HOME_BIN);
	char *n = r_str_newf ("%s%s%s", h, R_SYS_ENVSEP, e);
	r_sys_setenv ("PATH", n);
	free (n);
	free (h);
	free (e);
}