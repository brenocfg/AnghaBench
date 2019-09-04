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
typedef  int u32 ;
struct irq_domain {int dummy; } ;
struct irq_data {int hwirq; } ;
struct altera_msi {int /*<<< orphan*/  lock; int /*<<< orphan*/  used; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSI_INTMASK ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct altera_msi* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int msi_readl (struct altera_msi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_writel (struct altera_msi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void altera_irq_domain_free(struct irq_domain *domain,
				   unsigned int virq, unsigned int nr_irqs)
{
	struct irq_data *d = irq_domain_get_irq_data(domain, virq);
	struct altera_msi *msi = irq_data_get_irq_chip_data(d);
	u32 mask;

	mutex_lock(&msi->lock);

	if (!test_bit(d->hwirq, msi->used)) {
		dev_err(&msi->pdev->dev, "trying to free unused MSI#%lu\n",
			d->hwirq);
	} else {
		__clear_bit(d->hwirq, msi->used);
		mask = msi_readl(msi, MSI_INTMASK);
		mask &= ~(1 << d->hwirq);
		msi_writel(msi, mask, MSI_INTMASK);
	}

	mutex_unlock(&msi->lock);
}