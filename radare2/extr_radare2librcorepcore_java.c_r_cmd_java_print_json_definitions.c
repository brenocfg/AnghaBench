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
typedef  int /*<<< orphan*/  RBinJavaObj ;
typedef  int /*<<< orphan*/  DsoJsonObj ;

/* Variables and functions */
 int /*<<< orphan*/  dso_json_obj_del (int /*<<< orphan*/ *) ; 
 char* dso_json_obj_to_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_bin_java_get_bin_obj_json (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 

__attribute__((used)) static int r_cmd_java_print_json_definitions( RBinJavaObj *obj ) {
	DsoJsonObj *json_obj = r_bin_java_get_bin_obj_json (obj);
	char *str = dso_json_obj_to_str (json_obj);
	dso_json_obj_del (json_obj); // XXX memleak
	r_cons_println (str);
	return true;
}