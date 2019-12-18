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
struct action_item {unsigned int key_id; int expect_delta; int expect_root; int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_GET ; 
 int /*<<< orphan*/  ACTION_PUT ; 
 int EINVAL ; 
#define  EXPECT_DELTA_DEC 133 
#define  EXPECT_DELTA_INC 132 
#define  EXPECT_DELTA_SAME 131 
#define  EXPECT_ROOT_DEC 130 
#define  EXPECT_ROOT_INC 129 
#define  EXPECT_ROOT_SAME 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static int check_expect(struct world *world,
			const struct action_item *action_item,
			unsigned int orig_delta_count,
			unsigned int orig_root_count)
{
	unsigned int key_id = action_item->key_id;

	switch (action_item->expect_delta) {
	case EXPECT_DELTA_SAME:
		if (orig_delta_count != world->delta_count) {
			pr_err("Key %u: Delta count changed while expected to remain the same.\n",
			       key_id);
			return -EINVAL;
		}
		break;
	case EXPECT_DELTA_INC:
		if (WARN_ON(action_item->action == ACTION_PUT))
			return -EINVAL;
		if (orig_delta_count + 1 != world->delta_count) {
			pr_err("Key %u: Delta count was not incremented.\n",
			       key_id);
			return -EINVAL;
		}
		break;
	case EXPECT_DELTA_DEC:
		if (WARN_ON(action_item->action == ACTION_GET))
			return -EINVAL;
		if (orig_delta_count - 1 != world->delta_count) {
			pr_err("Key %u: Delta count was not decremented.\n",
			       key_id);
			return -EINVAL;
		}
		break;
	}

	switch (action_item->expect_root) {
	case EXPECT_ROOT_SAME:
		if (orig_root_count != world->root_count) {
			pr_err("Key %u: Root count changed while expected to remain the same.\n",
			       key_id);
			return -EINVAL;
		}
		break;
	case EXPECT_ROOT_INC:
		if (WARN_ON(action_item->action == ACTION_PUT))
			return -EINVAL;
		if (orig_root_count + 1 != world->root_count) {
			pr_err("Key %u: Root count was not incremented.\n",
			       key_id);
			return -EINVAL;
		}
		break;
	case EXPECT_ROOT_DEC:
		if (WARN_ON(action_item->action == ACTION_GET))
			return -EINVAL;
		if (orig_root_count - 1 != world->root_count) {
			pr_err("Key %u: Root count was not decremented.\n",
			       key_id);
			return -EINVAL;
		}
	}

	return 0;
}