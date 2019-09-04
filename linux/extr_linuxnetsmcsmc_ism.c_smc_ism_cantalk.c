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
typedef  int /*<<< orphan*/  u64 ;
struct smcd_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* query_remote_gid ) (struct smcd_dev*,int /*<<< orphan*/ ,int,unsigned short) ;} ;

/* Variables and functions */
 int stub1 (struct smcd_dev*,int /*<<< orphan*/ ,int,unsigned short) ; 

int smc_ism_cantalk(u64 peer_gid, unsigned short vlan_id, struct smcd_dev *smcd)
{
	return smcd->ops->query_remote_gid(smcd, peer_gid, vlan_id ? 1 : 0,
					   vlan_id);
}