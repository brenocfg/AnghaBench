#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  json_dict; } ;
struct TYPE_7__ {TYPE_6__* _dict; } ;
struct TYPE_8__ {TYPE_1__ val; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  RListFree ;
typedef  TYPE_2__ DsoJsonObj ;
typedef  int /*<<< orphan*/  DsoJsonDict ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_JSON_DICT ; 
 TYPE_6__* calloc (int,int) ; 
 int /*<<< orphan*/  dso_json_null_free (TYPE_2__*) ; 
 TYPE_2__* dso_json_null_new () ; 
 scalar_t__ dso_json_obj_del ; 
 int /*<<< orphan*/  get_type_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_newf (int /*<<< orphan*/ ) ; 

DsoJsonObj * dso_json_dict_new () {
	DsoJsonObj *x = dso_json_null_new ();
	if (x) {
		x->info = get_type_info (DSO_JSON_DICT);
		x->val._dict = calloc (sizeof (DsoJsonDict), 1);
		if (!x->val._dict) {
			dso_json_null_free (x);
			return NULL;
		}
		x->val._dict->json_dict = r_list_newf ((RListFree)dso_json_obj_del);
	}
	return x;
}