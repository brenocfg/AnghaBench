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
typedef  void* u64 ;
struct resource {int flags; void* end; void* start; } ;

/* Variables and functions */
 int IORESOURCE_BUSY ; 
 int IORESOURCE_SYSTEM_RAM ; 
 int /*<<< orphan*/  IORES_DESC_NONE ; 
 int __walk_iomem_res_desc (struct resource*,int /*<<< orphan*/ ,int,void*,int (*) (struct resource*,void*)) ; 

int walk_system_ram_res(u64 start, u64 end, void *arg,
				int (*func)(struct resource *, void *))
{
	struct resource res;

	res.start = start;
	res.end = end;
	res.flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	return __walk_iomem_res_desc(&res, IORES_DESC_NONE, true,
				     arg, func);
}