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
struct objagg_obj {void const* delta_priv; } ;

/* Variables and functions */
 scalar_t__ objagg_obj_is_root (struct objagg_obj const*) ; 

const void *objagg_obj_delta_priv(const struct objagg_obj *objagg_obj)
{
	if (objagg_obj_is_root(objagg_obj))
		return NULL;
	return objagg_obj->delta_priv;
}