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
struct TYPE_3__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  vlan_id; TYPE_1__ hdr; } ;
union ism_set_vlan_id {TYPE_2__ request; } ;
typedef  int /*<<< orphan*/  u64 ;
struct smcd_dev {struct ism_dev* priv; } ;
struct ism_dev {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ISM_ADD_VLAN_ID ; 
 int ism_cmd (struct ism_dev*,union ism_set_vlan_id*) ; 
 int /*<<< orphan*/  memset (union ism_set_vlan_id*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ism_add_vlan_id(struct smcd_dev *smcd, u64 vlan_id)
{
	struct ism_dev *ism = smcd->priv;
	union ism_set_vlan_id cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.request.hdr.cmd = ISM_ADD_VLAN_ID;
	cmd.request.hdr.len = sizeof(cmd.request);

	cmd.request.vlan_id = vlan_id;

	return ism_cmd(ism, &cmd);
}