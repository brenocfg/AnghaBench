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
struct TYPE_2__ {struct device* dev; } ;
struct tegra_msi {int /*<<< orphan*/  lock; int /*<<< orphan*/  used; TYPE_1__ chip; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_msi_free(struct tegra_msi *chip, unsigned long irq)
{
	struct device *dev = chip->chip.dev;

	mutex_lock(&chip->lock);

	if (!test_bit(irq, chip->used))
		dev_err(dev, "trying to free unused MSI#%lu\n", irq);
	else
		clear_bit(irq, chip->used);

	mutex_unlock(&chip->lock);
}