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
struct gen_pool {char const* name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct gen_pool* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_gen_pool_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct gen_pool**) ; 
 struct gen_pool** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct gen_pool**) ; 
 struct gen_pool* gen_pool_create (int,int) ; 
 scalar_t__ gen_pool_get (struct device*,char const*) ; 
 int /*<<< orphan*/  kfree_const (char const*) ; 
 char* kstrdup_const (char const*,int /*<<< orphan*/ ) ; 

struct gen_pool *devm_gen_pool_create(struct device *dev, int min_alloc_order,
				      int nid, const char *name)
{
	struct gen_pool **ptr, *pool;
	const char *pool_name = NULL;

	/* Check that genpool to be created is uniquely addressed on device */
	if (gen_pool_get(dev, name))
		return ERR_PTR(-EINVAL);

	if (name) {
		pool_name = kstrdup_const(name, GFP_KERNEL);
		if (!pool_name)
			return ERR_PTR(-ENOMEM);
	}

	ptr = devres_alloc(devm_gen_pool_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		goto free_pool_name;

	pool = gen_pool_create(min_alloc_order, nid);
	if (!pool)
		goto free_devres;

	*ptr = pool;
	pool->name = pool_name;
	devres_add(dev, ptr);

	return pool;

free_devres:
	devres_free(ptr);
free_pool_name:
	kfree_const(pool_name);

	return ERR_PTR(-ENOMEM);
}