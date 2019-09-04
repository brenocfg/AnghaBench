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
struct snd_amd7930 {scalar_t__ regs; scalar_t__ irq; struct platform_device* op; } ;
struct platform_device {int /*<<< orphan*/ * resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd7930_idle (struct snd_amd7930*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_amd7930*) ; 
 int /*<<< orphan*/  kfree (struct snd_amd7930*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_amd7930_free(struct snd_amd7930 *amd)
{
	struct platform_device *op = amd->op;

	amd7930_idle(amd);

	if (amd->irq)
		free_irq(amd->irq, amd);

	if (amd->regs)
		of_iounmap(&op->resource[0], amd->regs,
			   resource_size(&op->resource[0]));

	kfree(amd);

	return 0;
}