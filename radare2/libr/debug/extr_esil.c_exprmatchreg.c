#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_6__ {int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */
 scalar_t__ CURVAL ; 
 int exprmatch (TYPE_1__*,scalar_t__,char*) ; 
 scalar_t__ exprtoken (TYPE_1__*,char*,char*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_debug_reg_get_err (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ r_num_math (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_str_trim_head_tail (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int exprmatchreg (RDebug *dbg, const char *regname, const char *expr) {
	int ret = 0;
	char *p;
	char *s = strdup (expr);
	if (!s) {
		return 0;
	}
	if (!strcmp (regname, s)) {
		ret = 1;
	} else {
#define CURVAL 0){}r_str_trim_head_tail (s);if (!strcmp(regname,s) && regval
		ut64 regval = r_debug_reg_get_err (dbg, regname, NULL, NULL);
		if (exprtoken (dbg, s, ">=", &p)) {
			if (CURVAL >= r_num_math (dbg->num, p))
				ret = 1;
		} else if (exprtoken (dbg, s, "<=", &p)) {
			if (CURVAL <= r_num_math (dbg->num, p))
				ret = 1;
		} else if (exprtoken (dbg, s, "==", &p)) {
			if (CURVAL <= r_num_math (dbg->num, p))
				ret = 1;
		} else if (exprtoken (dbg, s, "<", &p)) {
			if (CURVAL < r_num_math (dbg->num, p))
				ret = 1;
		} else if (exprtoken (dbg, s, ">", &p)) {
			if (CURVAL > r_num_math (dbg->num, p))
				ret = 1;
		} else if (exprtoken (dbg, s, " ", &p)) {
			r_str_trim_head_tail (s);
			if (!strcmp (regname, s)) {
				ut64 num = r_num_math (dbg->num, p);
				ret = exprmatch (dbg, num, s);
			}
		} else {
			if (!strcmp (regname, s)) {
				ret = 1;
			}
		}
	}
	free (s);
	return ret;
}