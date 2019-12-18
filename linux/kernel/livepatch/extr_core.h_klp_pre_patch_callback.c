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
struct TYPE_2__ {int (* pre_patch ) (struct klp_object*) ;int post_unpatch_enabled; } ;
struct klp_object {TYPE_1__ callbacks; } ;

/* Variables and functions */
 int stub1 (struct klp_object*) ; 

__attribute__((used)) static inline int klp_pre_patch_callback(struct klp_object *obj)
{
	int ret = 0;

	if (obj->callbacks.pre_patch)
		ret = (*obj->callbacks.pre_patch)(obj);

	obj->callbacks.post_unpatch_enabled = !ret;

	return ret;
}