#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* value; } ;
struct TYPE_12__ {TYPE_3__* _dict_entry; } ;
struct TYPE_13__ {TYPE_1__ val; } ;
typedef  TYPE_2__ DsoJsonObj ;
typedef  TYPE_3__ DsoJsonDictEntry ;

/* Variables and functions */
 scalar_t__ dso_json_is_dict_entry (TYPE_2__*) ; 
 scalar_t__ dso_json_is_list (TYPE_2__*) ; 
 scalar_t__ dso_json_is_null (TYPE_2__*) ; 
 int /*<<< orphan*/  dso_json_list_append (TYPE_2__*,TYPE_2__*) ; 
 void* dso_json_list_new () ; 
 int /*<<< orphan*/  dso_json_obj_del (TYPE_2__*) ; 

int dso_json_dict_entry_value_append_obj (DsoJsonObj *entry_obj, DsoJsonObj *obj) {
	if (dso_json_is_dict_entry (entry_obj)) {
		DsoJsonDictEntry *x = entry_obj->val._dict_entry;

		// check to see if the object can be converted to a list
		if (dso_json_is_null (x->value)) {
			DsoJsonObj *new_list = dso_json_list_new ();
			dso_json_obj_del (x->value);
			x->value = new_list;
		} else if (!dso_json_is_list (x->value)) {
			DsoJsonObj *tmp = x->value;
			x->value = dso_json_list_new ();
			dso_json_list_append (x->value, tmp);
		}

		if (dso_json_is_list (x->value)) {
			dso_json_list_append (x->value, obj);
			return true;
		}
	}
	return false;
}