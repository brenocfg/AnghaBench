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
typedef  int /*<<< orphan*/  ulong ;
struct cxlflash_cfg {struct afu* afu; } ;
struct ctx_info {struct ctx_info* rht_lun; struct ctx_info* rht_needs_ws; scalar_t__ rht_start; TYPE_1__* ctrl_map; int /*<<< orphan*/  luns; scalar_t__ initialized; } ;
struct afu {scalar_t__ afu_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx_cap; int /*<<< orphan*/  rht_cnt_id; int /*<<< orphan*/  rht_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ctx_info*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeq_be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_context(struct cxlflash_cfg *cfg,
			    struct ctx_info *ctxi)
{
	struct afu *afu = cfg->afu;

	if (ctxi->initialized) {
		WARN_ON(!list_empty(&ctxi->luns));

		/* Clear RHT registers and drop all capabilities for context */
		if (afu->afu_map && ctxi->ctrl_map) {
			writeq_be(0, &ctxi->ctrl_map->rht_start);
			writeq_be(0, &ctxi->ctrl_map->rht_cnt_id);
			writeq_be(0, &ctxi->ctrl_map->ctx_cap);
		}
	}

	/* Free memory associated with context */
	free_page((ulong)ctxi->rht_start);
	kfree(ctxi->rht_needs_ws);
	kfree(ctxi->rht_lun);
	kfree(ctxi);
}