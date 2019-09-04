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
struct cppi_descriptor {int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct cppi_channel {int /*<<< orphan*/ * freelist; scalar_t__ is_rndis; struct cppi* controller; TYPE_1__ channel; int /*<<< orphan*/ * last_processed; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
struct cppi {int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MUSB_DMA_STATUS_UNKNOWN ; 
 int NUM_TXCHAN_BD ; 
 int /*<<< orphan*/  cppi_bd_free (struct cppi_channel*,struct cppi_descriptor*) ; 
 struct cppi_descriptor* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cppi_pool_init(struct cppi *cppi, struct cppi_channel *c)
{
	int	j;

	/* initialize channel fields */
	c->head = NULL;
	c->tail = NULL;
	c->last_processed = NULL;
	c->channel.status = MUSB_DMA_STATUS_UNKNOWN;
	c->controller = cppi;
	c->is_rndis = 0;
	c->freelist = NULL;

	/* build the BD Free list for the channel */
	for (j = 0; j < NUM_TXCHAN_BD + 1; j++) {
		struct cppi_descriptor	*bd;
		dma_addr_t		dma;

		bd = dma_pool_alloc(cppi->pool, GFP_KERNEL, &dma);
		bd->dma = dma;
		cppi_bd_free(c, bd);
	}
}