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
struct TYPE_4__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  dmb_tok; TYPE_2__ hdr; } ;
union ism_unreg_dmb {TYPE_1__ request; } ;
struct smcd_dmb {int /*<<< orphan*/  dmb_tok; } ;
struct smcd_dev {struct ism_dev* priv; } ;
struct ism_dev {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int ISM_ERROR ; 
 int /*<<< orphan*/  ISM_UNREG_DMB ; 
 int ism_cmd (struct ism_dev*,union ism_unreg_dmb*) ; 
 int /*<<< orphan*/  ism_free_dmb (struct ism_dev*,struct smcd_dmb*) ; 
 int /*<<< orphan*/  memset (union ism_unreg_dmb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ism_unregister_dmb(struct smcd_dev *smcd, struct smcd_dmb *dmb)
{
	struct ism_dev *ism = smcd->priv;
	union ism_unreg_dmb cmd;
	int ret;

	memset(&cmd, 0, sizeof(cmd));
	cmd.request.hdr.cmd = ISM_UNREG_DMB;
	cmd.request.hdr.len = sizeof(cmd.request);

	cmd.request.dmb_tok = dmb->dmb_tok;

	ret = ism_cmd(ism, &cmd);
	if (ret && ret != ISM_ERROR)
		goto out;

	ism_free_dmb(ism, dmb);
out:
	return ret;
}