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
struct ipw2100_priv {int /*<<< orphan*/  pci_dev; } ;
struct ipw2100_bd_queue {int /*<<< orphan*/ * drv; int /*<<< orphan*/  nic; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bd_queue_free(struct ipw2100_priv *priv, struct ipw2100_bd_queue *q)
{
	IPW_DEBUG_INFO("enter\n");

	if (!q)
		return;

	if (q->drv) {
		pci_free_consistent(priv->pci_dev, q->size, q->drv, q->nic);
		q->drv = NULL;
	}

	IPW_DEBUG_INFO("exit\n");
}