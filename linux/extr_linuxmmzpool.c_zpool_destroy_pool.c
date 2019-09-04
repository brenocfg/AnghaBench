#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zpool {TYPE_1__* driver; int /*<<< orphan*/  pool; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct zpool*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pools_lock ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_put_driver (TYPE_1__*) ; 

void zpool_destroy_pool(struct zpool *zpool)
{
	pr_debug("destroying pool type %s\n", zpool->driver->type);

	spin_lock(&pools_lock);
	list_del(&zpool->list);
	spin_unlock(&pools_lock);
	zpool->driver->destroy(zpool->pool);
	zpool_put_driver(zpool->driver);
	kfree(zpool);
}