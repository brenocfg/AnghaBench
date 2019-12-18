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
struct TYPE_2__ {scalar_t__ addr; } ;
struct snd_harmony {scalar_t__ irq; int /*<<< orphan*/  iobase; TYPE_1__ sdma; TYPE_1__ gdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_harmony*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_harmony*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 

__attribute__((used)) static int
snd_harmony_free(struct snd_harmony *h)
{
        if (h->gdma.addr)
                snd_dma_free_pages(&h->gdma);
        if (h->sdma.addr)
                snd_dma_free_pages(&h->sdma);

	if (h->irq >= 0)
		free_irq(h->irq, h);

	iounmap(h->iobase);
	kfree(h);
	return 0;
}