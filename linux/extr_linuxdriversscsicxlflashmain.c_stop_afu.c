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
struct hwq {int /*<<< orphan*/  irqpoll; } ;
struct cxlflash_cfg {TYPE_1__* ops; int /*<<< orphan*/  work_q; struct afu* afu; } ;
struct afu {int num_hwqs; struct afu* afu_map; int /*<<< orphan*/  cmds_active; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* psa_unmap ) (struct afu*) ;} ;

/* Variables and functions */
 scalar_t__ afu_is_irqpoll_enabled (struct afu*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_is_async () ; 
 int /*<<< orphan*/  cxlflash_reset_sync (struct cxlflash_cfg*) ; 
 struct hwq* get_hwq (struct afu*,int) ; 
 int /*<<< orphan*/  irq_poll_disable (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (struct afu*) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  stub1 (struct afu*) ; 

__attribute__((used)) static void stop_afu(struct cxlflash_cfg *cfg)
{
	struct afu *afu = cfg->afu;
	struct hwq *hwq;
	int i;

	cancel_work_sync(&cfg->work_q);
	if (!current_is_async())
		cxlflash_reset_sync(cfg);

	if (likely(afu)) {
		while (atomic_read(&afu->cmds_active))
			ssleep(1);

		if (afu_is_irqpoll_enabled(afu)) {
			for (i = 0; i < afu->num_hwqs; i++) {
				hwq = get_hwq(afu, i);

				irq_poll_disable(&hwq->irqpoll);
			}
		}

		if (likely(afu->afu_map)) {
			cfg->ops->psa_unmap(afu->afu_map);
			afu->afu_map = NULL;
		}
	}
}