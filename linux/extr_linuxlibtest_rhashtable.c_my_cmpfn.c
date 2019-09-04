#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct test_obj_val {int id; } ;
struct TYPE_2__ {int id; } ;
struct test_obj_rhl {TYPE_1__ value; } ;
struct rhashtable_compare_arg {struct test_obj_val* key; } ;

/* Variables and functions */

__attribute__((used)) static int my_cmpfn(struct rhashtable_compare_arg *arg, const void *obj)
{
	const struct test_obj_rhl *test_obj = obj;
	const struct test_obj_val *val = arg->key;

	return test_obj->value.id - val->id;
}