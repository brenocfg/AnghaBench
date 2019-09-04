#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ DsoJsonObj ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_JSON_NULL ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  get_type_info (int /*<<< orphan*/ ) ; 

DsoJsonObj * dso_json_null_new () {
	DsoJsonObj *x = calloc (sizeof (DsoJsonObj), 1);
	if (!x) return NULL;
	x->info = get_type_info (DSO_JSON_NULL);
	return x;
}