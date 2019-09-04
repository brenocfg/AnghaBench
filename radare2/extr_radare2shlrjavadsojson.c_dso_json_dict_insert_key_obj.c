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
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  DsoJsonObj ;

/* Variables and functions */
 scalar_t__ DSO_JSON_STR ; 
 int /*<<< orphan*/  dso_json_dict_contains_key_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dso_json_dict_entry_new_from_key_obj_val_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dso_json_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dso_json_dict_remove_key_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dso_json_get_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dso_json_null_new () ; 
 int /*<<< orphan*/  dso_json_obj_del (int /*<<< orphan*/ *) ; 
 scalar_t__ get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int dso_json_dict_insert_key_obj (DsoJsonObj *dict, DsoJsonObj *key, DsoJsonObj *value) {
	int res = false;
	RList* the_list = dso_json_get_list (dict);
	if (!the_list) return false;
	if (get_type (key) != DSO_JSON_STR) return false;
	if (!value) value = dso_json_null_new ();
	if (value && key && !dso_json_dict_contains_key_obj (dict, key)) {
		DsoJsonObj *entry = dso_json_dict_entry_new_from_key_obj_val_obj (key, value);
		r_list_append (the_list, entry);
		res = true;
	//TODO implement the remove key
	} else if (value && key && !dso_json_dict_remove_key_obj (dict, key)) {
		DsoJsonObj *entry = dso_json_dict_entry_new_from_key_obj_val_obj (key, value);
		r_list_append (the_list, entry);
		res = true;
	} else {
		dso_json_obj_del (value);
		dso_json_dict_free (value);
	}
	return res;
}