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
struct uniphier_aio_sub {scalar_t__ cstream; scalar_t__ substream; int /*<<< orphan*/  running; } ;
struct uniphier_aio_chip {int num_aios; struct uniphier_aio* aios; } ;
struct uniphier_aio {struct uniphier_aio_sub* sub; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  aiodma_compr_irq (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  aiodma_pcm_irq (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  aiodma_rb_is_irq (struct uniphier_aio_sub*) ; 
 struct uniphier_aio_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static irqreturn_t aiodma_irq(int irq, void *p)
{
	struct platform_device *pdev = p;
	struct uniphier_aio_chip *chip = platform_get_drvdata(pdev);
	irqreturn_t ret = IRQ_NONE;
	int i, j;

	for (i = 0; i < chip->num_aios; i++) {
		struct uniphier_aio *aio = &chip->aios[i];

		for (j = 0; j < ARRAY_SIZE(aio->sub); j++) {
			struct uniphier_aio_sub *sub = &aio->sub[j];

			/* Skip channel that does not trigger */
			if (!sub->running || !aiodma_rb_is_irq(sub))
				continue;

			if (sub->substream)
				aiodma_pcm_irq(sub);
			if (sub->cstream)
				aiodma_compr_irq(sub);

			ret = IRQ_HANDLED;
		}
	}

	return ret;
}