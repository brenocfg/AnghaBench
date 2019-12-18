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
struct world {int dummy; } ;
struct objagg {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct objagg*) ; 
 int PTR_ERR (struct objagg*) ; 
 int /*<<< orphan*/ * action_items ; 
 int /*<<< orphan*/  delta_ops ; 
 struct objagg* objagg_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct world*) ; 
 int /*<<< orphan*/  objagg_destroy (struct objagg*) ; 
 int test_delta_action_item (struct world*,struct objagg*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int test_delta(void)
{
	struct world world = {};
	struct objagg *objagg;
	int i;
	int err;

	objagg = objagg_create(&delta_ops, NULL, &world);
	if (IS_ERR(objagg))
		return PTR_ERR(objagg);

	for (i = 0; i < ARRAY_SIZE(action_items); i++) {
		err = test_delta_action_item(&world, objagg,
					     &action_items[i], false);
		if (err)
			goto err_do_action_item;
	}

	objagg_destroy(objagg);
	return 0;

err_do_action_item:
	for (i--; i >= 0; i--)
		test_delta_action_item(&world, objagg, &action_items[i], true);

	objagg_destroy(objagg);
	return err;
}