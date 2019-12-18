#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  _dict_entry; int /*<<< orphan*/  _dict; int /*<<< orphan*/  _list; int /*<<< orphan*/  _str; int /*<<< orphan*/  _num; } ;
struct TYPE_7__ {TYPE_2__ val; TYPE_1__* info; } ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_3__ DsoJsonObj ;

/* Variables and functions */
#define  DSO_JSON_DICT 133 
#define  DSO_JSON_DICT_ENTRY 132 
#define  DSO_JSON_LIST 131 
#define  DSO_JSON_NULL 130 
#define  DSO_JSON_NUM 129 
#define  DSO_JSON_STR 128 
 char* dso_json_dict_entry_to_str (int /*<<< orphan*/ ) ; 
 char* dso_json_dict_to_str (int /*<<< orphan*/ ) ; 
 char* dso_json_list_to_str (int /*<<< orphan*/ ) ; 
 char* dso_json_num_to_str (int /*<<< orphan*/ ) ; 
 char* dso_json_str_to_str (int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 

char * dso_json_obj_to_str (DsoJsonObj * dso_obj) {
	if (dso_obj && dso_obj->info) {
		switch (dso_obj->info->type) {
		case DSO_JSON_NULL: return strdup ("null");
		case DSO_JSON_NUM: return dso_json_num_to_str (dso_obj->val._num);
		case DSO_JSON_STR: return dso_json_str_to_str (dso_obj->val._str);
		case DSO_JSON_LIST: return dso_json_list_to_str (dso_obj->val._list);
		case DSO_JSON_DICT: return dso_json_dict_to_str (dso_obj->val._dict);
		case DSO_JSON_DICT_ENTRY: return dso_json_dict_entry_to_str (dso_obj->val._dict_entry);
		}
	}
	return NULL;
}