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
struct TYPE_2__ {int /*<<< orphan*/ * irqs; } ;
struct platform_device {int /*<<< orphan*/ * resource; TYPE_1__ archdata; int /*<<< orphan*/  dev; } ;
struct bbc_i2c_bus {scalar_t__ i2c_control_regs; scalar_t__ i2c_bussel_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  bbc_envctrl_cleanup (struct bbc_i2c_bus*) ; 
 struct bbc_i2c_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bbc_i2c_bus*) ; 
 int /*<<< orphan*/  kfree (struct bbc_i2c_bus*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int bbc_i2c_remove(struct platform_device *op)
{
	struct bbc_i2c_bus *bp = dev_get_drvdata(&op->dev);

	bbc_envctrl_cleanup(bp);

	free_irq(op->archdata.irqs[0], bp);

	if (bp->i2c_bussel_reg)
		of_iounmap(&op->resource[0], bp->i2c_bussel_reg, 1);
	if (bp->i2c_control_regs)
		of_iounmap(&op->resource[1], bp->i2c_control_regs, 2);

	kfree(bp);

	return 0;
}