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
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * values; } ;
typedef  TYPE_1__ RCFValueArray ;

/* Variables and functions */
 int /*<<< orphan*/  R_CF_INVALID ; 
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_cf_value_array_free(RCFValueArray *array) {
	if (!array) {
		return;
	}

	if (array->values) {
		r_list_free (array->values);
		array->values = NULL;
	}

	array->type = R_CF_INVALID;
	R_FREE (array);
}