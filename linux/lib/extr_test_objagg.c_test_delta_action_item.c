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
struct world {unsigned int delta_count; unsigned int root_count; } ;
struct objagg_obj {int dummy; } ;
struct objagg {int dummy; } ;
struct action_item {unsigned int key_id; int action; int /*<<< orphan*/  expect_stats; } ;
typedef  enum action { ____Placeholder_action } action ;

/* Variables and functions */
#define  ACTION_GET 129 
#define  ACTION_PUT 128 
 int /*<<< orphan*/  IS_ERR (struct objagg_obj*) ; 
 int PTR_ERR (struct objagg_obj*) ; 
 int check_expect (struct world*,struct action_item const*,unsigned int,unsigned int) ; 
 int check_expect_stats (struct objagg*,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,char const*) ; 
 struct objagg_obj* world_obj_get (struct world*,struct objagg*,unsigned int) ; 
 int /*<<< orphan*/  world_obj_put (struct world*,struct objagg*,unsigned int) ; 

__attribute__((used)) static int test_delta_action_item(struct world *world,
				  struct objagg *objagg,
				  const struct action_item *action_item,
				  bool inverse)
{
	unsigned int orig_delta_count = world->delta_count;
	unsigned int orig_root_count = world->root_count;
	unsigned int key_id = action_item->key_id;
	enum action action = action_item->action;
	struct objagg_obj *objagg_obj;
	const char *errmsg;
	int err;

	if (inverse)
		action = action == ACTION_GET ? ACTION_PUT : ACTION_GET;

	switch (action) {
	case ACTION_GET:
		objagg_obj = world_obj_get(world, objagg, key_id);
		if (IS_ERR(objagg_obj))
			return PTR_ERR(objagg_obj);
		break;
	case ACTION_PUT:
		world_obj_put(world, objagg, key_id);
		break;
	}

	if (inverse)
		return 0;
	err = check_expect(world, action_item,
			   orig_delta_count, orig_root_count);
	if (err)
		goto errout;

	err = check_expect_stats(objagg, &action_item->expect_stats, &errmsg);
	if (err) {
		pr_err("Key %u: Stats: %s\n", action_item->key_id, errmsg);
		goto errout;
	}

	return 0;

errout:
	/* This can only happen when action is not inversed.
	 * So in case of an error, cleanup by doing inverse action.
	 */
	test_delta_action_item(world, objagg, action_item, true);
	return err;
}