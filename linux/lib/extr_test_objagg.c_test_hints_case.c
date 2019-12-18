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
struct objagg_obj {int dummy; } ;
typedef  struct objagg_obj objagg_hints ;
typedef  struct objagg_obj objagg ;
struct hints_case {int key_ids_count; int /*<<< orphan*/ * key_ids; int /*<<< orphan*/  expect_stats_hints; int /*<<< orphan*/  expect_stats; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct objagg_obj*) ; 
 int /*<<< orphan*/  OBJAGG_OPT_ALGO_SIMPLE_GREEDY ; 
 int PTR_ERR (struct objagg_obj*) ; 
 int check_expect_hints_stats (struct objagg_obj*,int /*<<< orphan*/ *,char const**) ; 
 int check_expect_stats (struct objagg_obj*,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  delta_ops ; 
 struct objagg_obj* objagg_create (int /*<<< orphan*/ *,struct objagg_obj*,struct world*) ; 
 int /*<<< orphan*/  objagg_destroy (struct objagg_obj*) ; 
 struct objagg_obj* objagg_hints_get (struct objagg_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objagg_hints_put (struct objagg_obj*) ; 
 int /*<<< orphan*/  pr_debug_hints_stats (struct objagg_obj*) ; 
 int /*<<< orphan*/  pr_debug_stats (struct objagg_obj*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 struct objagg_obj* world_obj_get (struct world*,struct objagg_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  world_obj_put (struct world*,struct objagg_obj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_hints_case(const struct hints_case *hints_case)
{
	struct objagg_obj *objagg_obj;
	struct objagg_hints *hints;
	struct world world2 = {};
	struct world world = {};
	struct objagg *objagg2;
	struct objagg *objagg;
	const char *errmsg;
	int i;
	int err;

	objagg = objagg_create(&delta_ops, NULL, &world);
	if (IS_ERR(objagg))
		return PTR_ERR(objagg);

	for (i = 0; i < hints_case->key_ids_count; i++) {
		objagg_obj = world_obj_get(&world, objagg,
					   hints_case->key_ids[i]);
		if (IS_ERR(objagg_obj)) {
			err = PTR_ERR(objagg_obj);
			goto err_world_obj_get;
		}
	}

	pr_debug_stats(objagg);
	err = check_expect_stats(objagg, &hints_case->expect_stats, &errmsg);
	if (err) {
		pr_err("Stats: %s\n", errmsg);
		goto err_check_expect_stats;
	}

	hints = objagg_hints_get(objagg, OBJAGG_OPT_ALGO_SIMPLE_GREEDY);
	if (IS_ERR(hints)) {
		err = PTR_ERR(hints);
		goto err_hints_get;
	}

	pr_debug_hints_stats(hints);
	err = check_expect_hints_stats(hints, &hints_case->expect_stats_hints,
				       &errmsg);
	if (err) {
		pr_err("Hints stats: %s\n", errmsg);
		goto err_check_expect_hints_stats;
	}

	objagg2 = objagg_create(&delta_ops, hints, &world2);
	if (IS_ERR(objagg2))
		return PTR_ERR(objagg2);

	for (i = 0; i < hints_case->key_ids_count; i++) {
		objagg_obj = world_obj_get(&world2, objagg2,
					   hints_case->key_ids[i]);
		if (IS_ERR(objagg_obj)) {
			err = PTR_ERR(objagg_obj);
			goto err_world2_obj_get;
		}
	}

	pr_debug_stats(objagg2);
	err = check_expect_stats(objagg2, &hints_case->expect_stats_hints,
				 &errmsg);
	if (err) {
		pr_err("Stats2: %s\n", errmsg);
		goto err_check_expect_stats2;
	}

	err = 0;

err_check_expect_stats2:
err_world2_obj_get:
	for (i--; i >= 0; i--)
		world_obj_put(&world2, objagg, hints_case->key_ids[i]);
	objagg_hints_put(hints);
	objagg_destroy(objagg2);
	i = hints_case->key_ids_count;
err_check_expect_hints_stats:
err_hints_get:
err_check_expect_stats:
err_world_obj_get:
	for (i--; i >= 0; i--)
		world_obj_put(&world, objagg, hints_case->key_ids[i]);

	objagg_destroy(objagg);
	return err;
}