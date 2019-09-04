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
struct parman_ops {size_t algo; int /*<<< orphan*/  base_count; } ;
struct parman {int /*<<< orphan*/  algo; int /*<<< orphan*/  limit_count; void* priv; struct parman_ops const* ops; int /*<<< orphan*/  prio_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct parman* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parman_algos ; 

struct parman *parman_create(const struct parman_ops *ops, void *priv)
{
	struct parman *parman;

	parman = kzalloc(sizeof(*parman), GFP_KERNEL);
	if (!parman)
		return NULL;
	INIT_LIST_HEAD(&parman->prio_list);
	parman->ops = ops;
	parman->priv = priv;
	parman->limit_count = ops->base_count;
	parman->algo = parman_algos[ops->algo];
	return parman;
}