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
typedef  enum zpool_mapmode { ____Placeholder_zpool_mapmode } zpool_mapmode ;
struct TYPE_2__ {void* (* map ) (int /*<<< orphan*/ ,unsigned long,int) ;} ;

/* Variables and functions */
 void* stub1 (int /*<<< orphan*/ ,unsigned long,int) ; 

void *zpool_map_handle(struct zpool *zpool, unsigned long handle,
			enum zpool_mapmode mapmode)
{
	return zpool->driver->map(zpool->pool, handle, mapmode);
}