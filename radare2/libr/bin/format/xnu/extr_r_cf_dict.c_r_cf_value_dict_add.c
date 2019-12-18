#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pairs; } ;
typedef  TYPE_1__ RCFValueDict ;
typedef  int /*<<< orphan*/  RCFKeyValue ;

/* Variables and functions */
 int /*<<< orphan*/  r_list_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_cf_value_dict_add(RCFValueDict *dict, RCFKeyValue *key_value) {
	if (!dict || !dict->pairs) {
		return;
	}

	r_list_push (dict->pairs, key_value);
}