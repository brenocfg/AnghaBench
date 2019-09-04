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
struct parport_pc_private {scalar_t__ ecr; } ;
struct parport {scalar_t__ dma; struct parport_pc_private* private_data; } ;

/* Variables and functions */
 scalar_t__ PARPORT_DMA_NONE ; 
 scalar_t__ get_superio_dma (struct parport*) ; 
 scalar_t__ programmable_dma_support (struct parport*) ; 

__attribute__((used)) static int parport_dma_probe(struct parport *p)
{
	const struct parport_pc_private *priv = p->private_data;
	if (priv->ecr)		/* ask ECP chipset first */
		p->dma = programmable_dma_support(p);
	if (p->dma == PARPORT_DMA_NONE) {
		/* ask known Super-IO chips proper, although these
		   claim ECP compatible, some don't report their DMA
		   conforming to ECP standards */
		p->dma = get_superio_dma(p);
	}

	return p->dma;
}