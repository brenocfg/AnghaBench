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
struct il_priv {int /*<<< orphan*/  irq_tasklet; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
il3945_synchronize_irq(struct il_priv *il)
{
	/* wait to make sure we flush pending tasklet */
	synchronize_irq(il->pci_dev->irq);
	tasklet_kill(&il->irq_tasklet);
}