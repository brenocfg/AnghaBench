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
struct zpool {int /*<<< orphan*/  pool; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* shrink ) (int /*<<< orphan*/ ,unsigned int,unsigned int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

int zpool_shrink(struct zpool *zpool, unsigned int pages,
			unsigned int *reclaimed)
{
	return zpool->driver->shrink ?
	       zpool->driver->shrink(zpool->pool, pages, reclaimed) : -EINVAL;
}