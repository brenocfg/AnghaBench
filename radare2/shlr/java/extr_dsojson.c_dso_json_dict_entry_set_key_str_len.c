#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * key; } ;
typedef  int /*<<< orphan*/  DsoJsonObj ;
typedef  TYPE_1__ DsoJsonDictEntry ;

/* Variables and functions */
 scalar_t__ dso_json_is_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dso_json_obj_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dso_json_str_new_from_str_len (char*,unsigned int) ; 

int dso_json_dict_entry_set_key_str_len (DsoJsonObj * entry_obj, char *key, unsigned int len) {
	int res = false;
	if (dso_json_is_dict_entry (entry_obj)) {
		DsoJsonDictEntry *entry = (DsoJsonDictEntry *)entry_obj;
		DsoJsonObj *o_key = dso_json_str_new_from_str_len (key, len);
		if (entry->key) {
			dso_json_obj_del (entry->key);
		}
		entry->key = o_key;
		res = true;
	}
	return res;
}