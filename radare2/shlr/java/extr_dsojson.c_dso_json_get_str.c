#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* _dict_entry; int /*<<< orphan*/ * _str; } ;
struct TYPE_9__ {TYPE_3__ val; TYPE_1__* info; } ;
struct TYPE_7__ {TYPE_4__* key; } ;
struct TYPE_6__ {int type; } ;
typedef  int /*<<< orphan*/  DsoJsonStr ;
typedef  TYPE_4__ DsoJsonObj ;

/* Variables and functions */
#define  DSO_JSON_DICT_ENTRY 129 
#define  DSO_JSON_STR 128 

__attribute__((used)) static DsoJsonStr * dso_json_get_str (DsoJsonObj *dso_obj) {
	DsoJsonStr * str = NULL;
	if (dso_obj) {
		switch (dso_obj->info->type) {
		case DSO_JSON_STR: str = dso_obj->val._str; break;
		case DSO_JSON_DICT_ENTRY: str = dso_json_get_str (dso_obj->val._dict_entry->key); break;
		default: break;
		}
	}
	return str;
}