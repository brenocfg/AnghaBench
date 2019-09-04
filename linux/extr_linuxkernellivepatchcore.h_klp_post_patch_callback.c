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
struct TYPE_2__ {int /*<<< orphan*/  (* post_patch ) (struct klp_object*) ;} ;
struct klp_object {TYPE_1__ callbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct klp_object*) ; 

__attribute__((used)) static inline void klp_post_patch_callback(struct klp_object *obj)
{
	if (obj->callbacks.post_patch)
		(*obj->callbacks.post_patch)(obj);
}