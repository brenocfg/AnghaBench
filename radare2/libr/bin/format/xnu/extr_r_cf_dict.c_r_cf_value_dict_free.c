#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * pairs; } ;
typedef  TYPE_1__ RCFValueDict ;

/* Variables and functions */
 int /*<<< orphan*/  R_CF_INVALID ; 
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_return_if_fail (TYPE_1__*) ; 

void r_cf_value_dict_free (RCFValueDict *dict) {
	r_return_if_fail (dict);

	if (dict->pairs) {
		r_list_free (dict->pairs);
		dict->pairs = NULL;
	}
	dict->type = R_CF_INVALID;
	R_FREE (dict);
}