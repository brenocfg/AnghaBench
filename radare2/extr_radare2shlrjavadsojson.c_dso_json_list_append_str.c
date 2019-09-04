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
typedef  int /*<<< orphan*/  DsoJsonObj ;

/* Variables and functions */
 scalar_t__ DSO_JSON_LIST ; 
 int dso_json_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dso_json_obj_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dso_json_str_new_from_str (char*) ; 
 scalar_t__ get_type (int /*<<< orphan*/ *) ; 

int dso_json_list_append_str (DsoJsonObj *list_obj, char *y) {
	if (get_type (list_obj) == DSO_JSON_LIST) {
		DsoJsonObj *val = dso_json_str_new_from_str (y);
		int res = dso_json_list_append (list_obj, val);
		if (!res) dso_json_obj_del (val);
		return res;
	}
	return false;
}