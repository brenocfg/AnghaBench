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
struct fsl_mc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_mc_free_irqs (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  unregister_dpio_irq_handlers (struct fsl_mc_device*) ; 

__attribute__((used)) static void dpio_teardown_irqs(struct fsl_mc_device *dpio_dev)
{
	unregister_dpio_irq_handlers(dpio_dev);
	fsl_mc_free_irqs(dpio_dev);
}