#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  json_list; } ;
struct TYPE_8__ {TYPE_3__* _list; } ;
struct TYPE_9__ {TYPE_1__ val; } ;
typedef  TYPE_2__ DsoJsonObj ;
typedef  TYPE_3__ DsoJsonList ;

/* Variables and functions */
 scalar_t__ DSO_JSON_LIST ; 
 scalar_t__ get_type (TYPE_2__*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ ,TYPE_2__*) ; 

int dso_json_list_append (DsoJsonObj *list_obj, DsoJsonObj *y) {
	if (get_type (list_obj) == DSO_JSON_LIST) {
		DsoJsonList * list = list_obj->val._list;
		r_list_append (list->json_list, y);
		return true;
	}
	return false;
}