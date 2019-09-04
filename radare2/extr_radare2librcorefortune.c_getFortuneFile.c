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
 int /*<<< orphan*/  R2_FORTUNES ; 
 int /*<<< orphan*/  R_JOIN_3_PATHS (char*,int /*<<< orphan*/ ,char*) ; 
 char* r_str_newf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_sys_prefix (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *getFortuneFile(RCore *core, const char *type) {
	return r_str_newf (R_JOIN_3_PATHS ("%s", R2_FORTUNES, "fortunes.%s"),
		r_sys_prefix (NULL), type);
}