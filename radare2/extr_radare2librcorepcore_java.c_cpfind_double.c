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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RCore ;
typedef  int /*<<< orphan*/  RBinJavaObj ;

/* Variables and functions */
 int /*<<< orphan*/  R_BIN_JAVA_CP_DOUBLE ; 
 int /*<<< orphan*/ * r_bin_java_find_cp_const_by_val (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_list_new () ; 
 double strtod (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RList * cpfind_double (RCore *core, RBinJavaObj *obj, const char *cmd) {
	double value = cmd && *cmd ? strtod (cmd, NULL) : 0.0;
	if (value == 0.0 && !(cmd && cmd[0] == '0' && cmd[1] == '.' && cmd[2] == '0')) {
		return r_list_new ();
	}
	return r_bin_java_find_cp_const_by_val ( obj, (const ut8 *) &value, 8, R_BIN_JAVA_CP_DOUBLE);
}