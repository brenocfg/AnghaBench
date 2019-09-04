#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smcd_dmb {int dmb_len; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  dmb_tok; int /*<<< orphan*/  sba_idx; int /*<<< orphan*/  rgid; int /*<<< orphan*/  vlan_id; } ;
struct smc_link_group {TYPE_2__* smcd; int /*<<< orphan*/  peer_gid; int /*<<< orphan*/  vlan_id; } ;
struct smc_buf_desc {int len; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  token; int /*<<< orphan*/  sba_idx; } ;
typedef  int /*<<< orphan*/  dmb ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* register_dmb ) (TYPE_2__*,struct smcd_dmb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct smcd_dmb*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_2__*,struct smcd_dmb*) ; 

int smc_ism_register_dmb(struct smc_link_group *lgr, int dmb_len,
			 struct smc_buf_desc *dmb_desc)
{
	struct smcd_dmb dmb;
	int rc;

	memset(&dmb, 0, sizeof(dmb));
	dmb.dmb_len = dmb_len;
	dmb.sba_idx = dmb_desc->sba_idx;
	dmb.vlan_id = lgr->vlan_id;
	dmb.rgid = lgr->peer_gid;
	rc = lgr->smcd->ops->register_dmb(lgr->smcd, &dmb);
	if (!rc) {
		dmb_desc->sba_idx = dmb.sba_idx;
		dmb_desc->token = dmb.dmb_tok;
		dmb_desc->cpu_addr = dmb.cpu_addr;
		dmb_desc->dma_addr = dmb.dma_addr;
		dmb_desc->len = dmb.dmb_len;
	}
	return rc;
}