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
typedef  int u32 ;
struct vme_bridge {struct ca91cx42_driver* driver_priv; } ;
struct ca91cx42_driver {scalar_t__ base; } ;

/* Variables and functions */
 int CA91CX42_DGCS_ACT ; 
 scalar_t__ DGCS ; 
 int ioread32 (scalar_t__) ; 

__attribute__((used)) static int ca91cx42_dma_busy(struct vme_bridge *ca91cx42_bridge)
{
	u32 tmp;
	struct ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	tmp = ioread32(bridge->base + DGCS);

	if (tmp & CA91CX42_DGCS_ACT)
		return 0;
	else
		return 1;
}