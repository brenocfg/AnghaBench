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
typedef  int /*<<< orphan*/  st64 ;
typedef  int /*<<< orphan*/  DsoJsonObj ;

/* Variables and functions */
 int dso_json_dict_entry_value_append_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dso_json_is_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dso_json_num_new_from_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso_json_obj_del (int /*<<< orphan*/ *) ; 

int dso_json_dict_entry_value_append_num (DsoJsonObj *entry_obj, st64 num) {
	int res = false;
	if (dso_json_is_dict_entry (entry_obj)) {
		DsoJsonObj *o_num = dso_json_num_new_from_num (num);
		res = dso_json_dict_entry_value_append_obj (entry_obj, o_num);
		if (!res) dso_json_obj_del (o_num);
	}
	return res;
}