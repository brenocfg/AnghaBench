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
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int (* malloc ) (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,unsigned long*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,unsigned long*) ; 

int zpool_malloc(struct zpool *zpool, size_t size, gfp_t gfp,
			unsigned long *handle)
{
	return zpool->driver->malloc(zpool->pool, size, gfp, handle);
}