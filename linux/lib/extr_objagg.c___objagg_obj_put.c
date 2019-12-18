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
struct objagg_obj {int dummy; } ;
struct objagg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  objagg_obj_destroy (struct objagg*,struct objagg_obj*) ; 
 int /*<<< orphan*/  objagg_obj_ref_dec (struct objagg_obj*) ; 

__attribute__((used)) static void __objagg_obj_put(struct objagg *objagg,
			     struct objagg_obj *objagg_obj)
{
	if (!objagg_obj_ref_dec(objagg_obj))
		objagg_obj_destroy(objagg, objagg_obj);
}