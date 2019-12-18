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
 struct objagg_obj* objagg_obj_create (struct objagg*,void*) ; 
 struct objagg_obj* objagg_obj_lookup (struct objagg*,void*) ; 
 int /*<<< orphan*/  objagg_obj_ref_inc (struct objagg_obj*) ; 

__attribute__((used)) static struct objagg_obj *__objagg_obj_get(struct objagg *objagg, void *obj)
{
	struct objagg_obj *objagg_obj;

	/* First, try to find the object exactly as user passed it,
	 * perhaps it is already in use.
	 */
	objagg_obj = objagg_obj_lookup(objagg, obj);
	if (objagg_obj) {
		objagg_obj_ref_inc(objagg_obj);
		return objagg_obj;
	}

	return objagg_obj_create(objagg, obj);
}