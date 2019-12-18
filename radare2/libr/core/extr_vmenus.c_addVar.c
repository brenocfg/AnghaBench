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
 char* __prompt (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_core_cmd0 (int /*<<< orphan*/ *,char*) ; 
 char* r_str_newf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  r_str_trim (char*) ; 

__attribute__((used)) static void addVar(RCore *core, int ch, const char *msg) {
	char *src = __prompt (msg, NULL);
	char *name = __prompt ("Variable Name: ", NULL);
	char *type = __prompt ("Type of Variable (int32_t): ", NULL);
	char *cmd = r_str_newf ("afv%c %s %s %s", ch, src, name, type);
	r_str_trim (cmd);
	r_core_cmd0 (core, cmd);
	free(cmd);
	free (src);
	free (name);
	free (type);
}