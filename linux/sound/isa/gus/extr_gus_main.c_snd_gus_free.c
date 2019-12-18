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
struct TYPE_2__ {scalar_t__ irq; scalar_t__ dma1; scalar_t__ dma2; int /*<<< orphan*/ * res_port2; int /*<<< orphan*/ * res_port1; } ;
struct snd_gus_card {TYPE_1__ gf1; int /*<<< orphan*/  equal_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  kfree (struct snd_gus_card*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_gf1_stop (struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_gus_init_dma_irq (struct snd_gus_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_gus_free(struct snd_gus_card *gus)
{
	if (gus->gf1.res_port2 == NULL)
		goto __hw_end;
	snd_gf1_stop(gus);
	snd_gus_init_dma_irq(gus, 0);
      __hw_end:
	release_and_free_resource(gus->gf1.res_port1);
	release_and_free_resource(gus->gf1.res_port2);
	if (gus->gf1.irq >= 0)
		free_irq(gus->gf1.irq, (void *) gus);
	if (gus->gf1.dma1 >= 0) {
		disable_dma(gus->gf1.dma1);
		free_dma(gus->gf1.dma1);
	}
	if (!gus->equal_dma && gus->gf1.dma2 >= 0) {
		disable_dma(gus->gf1.dma2);
		free_dma(gus->gf1.dma2);
	}
	kfree(gus);
	return 0;
}