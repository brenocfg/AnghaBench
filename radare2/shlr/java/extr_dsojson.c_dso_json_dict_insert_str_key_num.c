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
 int dso_json_dict_insert_key_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dso_json_num_new_from_num (int) ; 
 int /*<<< orphan*/  dso_json_obj_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dso_json_str_new_from_str (char*) ; 

int dso_json_dict_insert_str_key_num (DsoJsonObj *dict, char *key, int val) {
	DsoJsonObj *key_obj = dso_json_str_new_from_str (key);
	DsoJsonObj *val_obj = dso_json_num_new_from_num (val);
	int res = dso_json_dict_insert_key_obj (dict, key_obj, val_obj);
	if (!res) {
		dso_json_obj_del (key_obj);
	}
	return res;
}