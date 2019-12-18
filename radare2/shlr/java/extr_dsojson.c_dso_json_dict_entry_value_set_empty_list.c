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
 int dso_json_dict_entry_value_set_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dso_json_is_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dso_json_list_new () ; 

int dso_json_dict_entry_value_set_empty_list (DsoJsonObj *entry_obj) {
	int res = false;
	if (dso_json_is_dict_entry (entry_obj)) {
		DsoJsonObj *o_val = dso_json_list_new ();
		res = dso_json_dict_entry_value_set_obj (entry_obj, o_val);
	}
	return res;
}