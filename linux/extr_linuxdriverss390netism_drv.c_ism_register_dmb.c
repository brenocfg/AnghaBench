#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dmb_tok; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  rgid; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  vlan_valid; int /*<<< orphan*/  sba_idx; int /*<<< orphan*/  dmb_len; int /*<<< orphan*/  dmb; TYPE_1__ hdr; } ;
union ism_reg_dmb {TYPE_3__ response; TYPE_2__ request; } ;
struct smcd_dmb {int /*<<< orphan*/  dmb_tok; int /*<<< orphan*/  rgid; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  vlan_valid; int /*<<< orphan*/  sba_idx; int /*<<< orphan*/  dmb_len; int /*<<< orphan*/  dma_addr; } ;
struct smcd_dev {struct ism_dev* priv; } ;
struct ism_dev {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ISM_REG_DMB ; 
 int ism_alloc_dmb (struct ism_dev*,struct smcd_dmb*) ; 
 int ism_cmd (struct ism_dev*,union ism_reg_dmb*) ; 
 int /*<<< orphan*/  ism_free_dmb (struct ism_dev*,struct smcd_dmb*) ; 
 int /*<<< orphan*/  memset (union ism_reg_dmb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ism_register_dmb(struct smcd_dev *smcd, struct smcd_dmb *dmb)
{
	struct ism_dev *ism = smcd->priv;
	union ism_reg_dmb cmd;
	int ret;

	ret = ism_alloc_dmb(ism, dmb);
	if (ret)
		goto out;

	memset(&cmd, 0, sizeof(cmd));
	cmd.request.hdr.cmd = ISM_REG_DMB;
	cmd.request.hdr.len = sizeof(cmd.request);

	cmd.request.dmb = dmb->dma_addr;
	cmd.request.dmb_len = dmb->dmb_len;
	cmd.request.sba_idx = dmb->sba_idx;
	cmd.request.vlan_valid = dmb->vlan_valid;
	cmd.request.vlan_id = dmb->vlan_id;
	cmd.request.rgid = dmb->rgid;

	ret = ism_cmd(ism, &cmd);
	if (ret) {
		ism_free_dmb(ism, dmb);
		goto out;
	}
	dmb->dmb_tok = cmd.response.dmb_tok;
out:
	return ret;
}