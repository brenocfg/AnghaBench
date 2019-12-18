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
 int objagg_obj_init_with_hints (struct objagg*,struct objagg_obj*,int*) ; 
 int objagg_obj_parent_lookup_assign (struct objagg*,struct objagg_obj*) ; 
 int objagg_obj_root_create (struct objagg*,struct objagg_obj*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int objagg_obj_init(struct objagg *objagg,
			   struct objagg_obj *objagg_obj)
{
	bool hint_found;
	int err;

	/* First, try to use hints if they are available and
	 * if they provide result.
	 */
	err = objagg_obj_init_with_hints(objagg, objagg_obj, &hint_found);
	if (err)
		return err;

	if (hint_found)
		return 0;

	/* Try to find if the object can be aggregated under an existing one. */
	err = objagg_obj_parent_lookup_assign(objagg, objagg_obj);
	if (!err)
		return 0;
	/* If aggregation is not possible, make the object a root. */
	return objagg_obj_root_create(objagg, objagg_obj, NULL);
}