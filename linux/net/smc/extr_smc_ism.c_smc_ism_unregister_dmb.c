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
struct smcd_dmb {int /*<<< orphan*/  dmb_len; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  sba_idx; int /*<<< orphan*/  dmb_tok; } ;
struct smcd_dev {TYPE_1__* ops; } ;
struct smc_buf_desc {int /*<<< orphan*/  len; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  sba_idx; int /*<<< orphan*/  token; } ;
typedef  int /*<<< orphan*/  dmb ;
struct TYPE_2__ {int (* unregister_dmb ) (struct smcd_dev*,struct smcd_dmb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct smcd_dmb*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct smcd_dev*,struct smcd_dmb*) ; 

int smc_ism_unregister_dmb(struct smcd_dev *smcd, struct smc_buf_desc *dmb_desc)
{
	struct smcd_dmb dmb;

	memset(&dmb, 0, sizeof(dmb));
	dmb.dmb_tok = dmb_desc->token;
	dmb.sba_idx = dmb_desc->sba_idx;
	dmb.cpu_addr = dmb_desc->cpu_addr;
	dmb.dma_addr = dmb_desc->dma_addr;
	dmb.dmb_len = dmb_desc->len;
	return smcd->ops->unregister_dmb(smcd, &dmb);
}