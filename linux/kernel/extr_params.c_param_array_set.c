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
struct kparam_array {scalar_t__ num; TYPE_1__* ops; int /*<<< orphan*/  elemsize; int /*<<< orphan*/  elem; int /*<<< orphan*/  max; } ;
struct kernel_param {int /*<<< orphan*/  level; int /*<<< orphan*/  name; int /*<<< orphan*/  mod; struct kparam_array* arr; } ;
struct TYPE_2__ {int /*<<< orphan*/  set; } ;

/* Variables and functions */
 int param_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int param_array_set(const char *val, const struct kernel_param *kp)
{
	const struct kparam_array *arr = kp->arr;
	unsigned int temp_num;

	return param_array(kp->mod, kp->name, val, 1, arr->max, arr->elem,
			   arr->elemsize, arr->ops->set, kp->level,
			   arr->num ?: &temp_num);
}