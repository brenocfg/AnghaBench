#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* _dict_entry; } ;
struct TYPE_11__ {TYPE_1__ val; } ;
struct TYPE_10__ {TYPE_3__* value; TYPE_3__* key; } ;
typedef  TYPE_3__ DsoJsonObj ;

/* Variables and functions */
 TYPE_3__* dso_json_dict_entry_new () ; 
 int /*<<< orphan*/  dso_json_obj_del (TYPE_3__*) ; 

DsoJsonObj * dso_json_dict_entry_new_from_key_obj_val_obj (DsoJsonObj *key, DsoJsonObj *value) {
	DsoJsonObj *x = dso_json_dict_entry_new ();
	if (!x) return NULL;
	dso_json_obj_del (x->val._dict_entry->key);
	dso_json_obj_del (x->val._dict_entry->value);
	x->val._dict_entry->key = key;
	x->val._dict_entry->value = value;
	return x;

}