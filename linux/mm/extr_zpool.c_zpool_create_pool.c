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
struct zpool_ops {scalar_t__ evict; } ;
struct zpool_driver {scalar_t__ shrink; int /*<<< orphan*/  (* create ) (char const*,int /*<<< orphan*/ ,struct zpool_ops const*,struct zpool*) ;} ;
struct zpool {int evictable; int /*<<< orphan*/  list; int /*<<< orphan*/  pool; struct zpool_ops const* ops; struct zpool_driver* driver; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct zpool*) ; 
 struct zpool* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pools_head ; 
 int /*<<< orphan*/  pools_lock ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/ ,struct zpool_ops const*,struct zpool*) ; 
 struct zpool_driver* zpool_get_driver (char const*) ; 
 int /*<<< orphan*/  zpool_put_driver (struct zpool_driver*) ; 

struct zpool *zpool_create_pool(const char *type, const char *name, gfp_t gfp,
		const struct zpool_ops *ops)
{
	struct zpool_driver *driver;
	struct zpool *zpool;

	pr_debug("creating pool type %s\n", type);

	driver = zpool_get_driver(type);

	if (!driver) {
		request_module("zpool-%s", type);
		driver = zpool_get_driver(type);
	}

	if (!driver) {
		pr_err("no driver for type %s\n", type);
		return NULL;
	}

	zpool = kmalloc(sizeof(*zpool), gfp);
	if (!zpool) {
		pr_err("couldn't create zpool - out of memory\n");
		zpool_put_driver(driver);
		return NULL;
	}

	zpool->driver = driver;
	zpool->pool = driver->create(name, gfp, ops, zpool);
	zpool->ops = ops;
	zpool->evictable = driver->shrink && ops && ops->evict;

	if (!zpool->pool) {
		pr_err("couldn't create %s pool\n", type);
		zpool_put_driver(driver);
		kfree(zpool);
		return NULL;
	}

	pr_debug("created pool type %s\n", type);

	spin_lock(&pools_lock);
	list_add(&zpool->list, &pools_head);
	spin_unlock(&pools_lock);

	return zpool;
}