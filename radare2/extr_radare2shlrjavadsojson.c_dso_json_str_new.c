#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  _str; } ;
struct TYPE_6__ {TYPE_1__ val; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  DsoJsonStr ;
typedef  TYPE_2__ DsoJsonObj ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_JSON_STR ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 TYPE_2__* dso_json_null_new () ; 
 int /*<<< orphan*/  get_type_info (int /*<<< orphan*/ ) ; 

DsoJsonObj * dso_json_str_new () {
	DsoJsonObj *x = dso_json_null_new ();
	if (!x) return NULL;
	x->info = get_type_info (DSO_JSON_STR);
	x->val._str = calloc (sizeof (DsoJsonStr), 1);
	return x;
}