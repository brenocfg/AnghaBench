#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  klp_shadow_ctor_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 void* __klp_shadow_get_or_alloc (void*,unsigned long,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

void *klp_shadow_alloc(void *obj, unsigned long id,
		       size_t size, gfp_t gfp_flags,
		       klp_shadow_ctor_t ctor, void *ctor_data)
{
	return __klp_shadow_get_or_alloc(obj, id, size, gfp_flags,
					 ctor, ctor_data, true);
}