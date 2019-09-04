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
struct vme_bridge {int /*<<< orphan*/  irq_mtx; int /*<<< orphan*/  lm_resources; int /*<<< orphan*/  dma_resources; int /*<<< orphan*/  slave_resources; int /*<<< orphan*/  master_resources; int /*<<< orphan*/  vme_error_handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct vme_bridge *vme_init_bridge(struct vme_bridge *bridge)
{
	INIT_LIST_HEAD(&bridge->vme_error_handlers);
	INIT_LIST_HEAD(&bridge->master_resources);
	INIT_LIST_HEAD(&bridge->slave_resources);
	INIT_LIST_HEAD(&bridge->dma_resources);
	INIT_LIST_HEAD(&bridge->lm_resources);
	mutex_init(&bridge->irq_mtx);

	return bridge;
}