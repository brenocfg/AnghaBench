#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* value; int /*<<< orphan*/  key; } ;
struct TYPE_6__ {TYPE_5__* _dict_entry; } ;
struct TYPE_7__ {TYPE_1__ val; int /*<<< orphan*/  info; } ;
typedef  TYPE_2__ DsoJsonObj ;
typedef  int /*<<< orphan*/  DsoJsonDictEntry ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_JSON_DICT_ENTRY ; 
 TYPE_5__* calloc (int,int) ; 
 int /*<<< orphan*/  dso_json_null_free (TYPE_2__*) ; 
 void* dso_json_null_new () ; 
 int /*<<< orphan*/  dso_json_str_new () ; 
 int /*<<< orphan*/  get_type_info (int /*<<< orphan*/ ) ; 

DsoJsonObj * dso_json_dict_entry_new () {
	DsoJsonObj *x = dso_json_null_new ();
	if (!x) return NULL;
	x->info = get_type_info (DSO_JSON_DICT_ENTRY);
	x->val._dict_entry = calloc (sizeof (DsoJsonDictEntry), 1);
	if (!x->val._dict_entry) {
		dso_json_null_free (x);
		return NULL;
	}
	x->val._dict_entry->key = dso_json_str_new ();
	x->val._dict_entry->value = dso_json_null_new ();
	return x;
}