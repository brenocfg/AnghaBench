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
struct resource {int dummy; } ;
struct dw_dma_chip {int irq; struct device* dev; int /*<<< orphan*/  regs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 struct dw_dma_chip* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct dw_dma_chip* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct dw_dma_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int dw_dma_probe (struct dw_dma_chip*) ; 

__attribute__((used)) static struct dw_dma_chip *dw_probe(struct device *dev, struct resource *mem,
	int irq)
{
	struct dw_dma_chip *chip;
	int err;

	chip = devm_kzalloc(dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return ERR_PTR(-ENOMEM);

	chip->irq = irq;
	chip->regs = devm_ioremap_resource(dev, mem);
	if (IS_ERR(chip->regs))
		return ERR_CAST(chip->regs);

	err = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(31));
	if (err)
		return ERR_PTR(err);

	chip->dev = dev;

	err = dw_dma_probe(chip);
	if (err)
		return ERR_PTR(err);

	return chip;
}