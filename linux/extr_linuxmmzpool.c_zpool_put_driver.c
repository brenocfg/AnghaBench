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
struct zpool_driver {int /*<<< orphan*/  owner; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zpool_put_driver(struct zpool_driver *driver)
{
	atomic_dec(&driver->refcount);
	module_put(driver->owner);
}