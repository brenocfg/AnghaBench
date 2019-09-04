#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* _dict; TYPE_2__* _list; } ;
struct TYPE_11__ {TYPE_4__ val; TYPE_1__* info; } ;
struct TYPE_9__ {int /*<<< orphan*/ * json_dict; } ;
struct TYPE_8__ {int /*<<< orphan*/ * json_list; } ;
struct TYPE_7__ {int type; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_5__ DsoJsonObj ;

/* Variables and functions */
#define  DSO_JSON_DICT 129 
#define  DSO_JSON_LIST 128 

__attribute__((used)) static RList * dso_json_get_list (DsoJsonObj *dso_obj) {
	RList *the_list = NULL;
	if (dso_obj) {
		switch (dso_obj->info->type) {
		case DSO_JSON_LIST: the_list = dso_obj->val._list->json_list; break;
		case DSO_JSON_DICT: the_list = dso_obj->val._dict->json_dict; break;
		default: break;
		}
	}
	return the_list;
}