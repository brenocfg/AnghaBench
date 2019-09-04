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
struct resource {unsigned long flags; } ;

/* Variables and functions */
 unsigned long IORESOURCE_BUS ; 
 unsigned long IORESOURCE_DMA ; 
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_IRQ ; 
 unsigned long IORESOURCE_MEM ; 

unsigned long pnp_resource_type(struct resource *res)
{
	return res->flags & (IORESOURCE_IO  | IORESOURCE_MEM |
			     IORESOURCE_IRQ | IORESOURCE_DMA |
			     IORESOURCE_BUS);
}