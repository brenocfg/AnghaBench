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
typedef  int u8 ;
struct smc_ib_device {int /*<<< orphan*/  ibdev; TYPE_1__* pattr; } ;
struct net_device {scalar_t__ gid_type; int index; int /*<<< orphan*/  gid; int /*<<< orphan*/  ndev; } ;
struct ib_gid_attr {scalar_t__ gid_type; int index; int /*<<< orphan*/  gid; int /*<<< orphan*/  ndev; } ;
struct TYPE_2__ {int gid_tbl_len; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IB_GID_TYPE_ROCE ; 
 scalar_t__ IS_ERR (struct net_device const*) ; 
 int /*<<< orphan*/  SMC_GID_SIZE ; 
 scalar_t__ is_vlan_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct net_device* rdma_get_gid_attr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rdma_put_gid_attr (struct net_device const*) ; 
 struct net_device* rdma_read_gid_attr_ndev_rcu (struct net_device const*) ; 
 unsigned short vlan_dev_vlan_id (int /*<<< orphan*/ ) ; 

int smc_ib_determine_gid(struct smc_ib_device *smcibdev, u8 ibport,
			 unsigned short vlan_id, u8 gid[], u8 *sgid_index)
{
	const struct ib_gid_attr *attr;
	const struct net_device *ndev;
	int i;

	for (i = 0; i < smcibdev->pattr[ibport - 1].gid_tbl_len; i++) {
		attr = rdma_get_gid_attr(smcibdev->ibdev, ibport, i);
		if (IS_ERR(attr))
			continue;

		rcu_read_lock();
		ndev = rdma_read_gid_attr_ndev_rcu(attr);
		if (!IS_ERR(ndev) &&
		    ((!vlan_id && !is_vlan_dev(attr->ndev)) ||
		     (vlan_id && is_vlan_dev(attr->ndev) &&
		      vlan_dev_vlan_id(attr->ndev) == vlan_id)) &&
		    attr->gid_type == IB_GID_TYPE_ROCE) {
			rcu_read_unlock();
			if (gid)
				memcpy(gid, &attr->gid, SMC_GID_SIZE);
			if (sgid_index)
				*sgid_index = attr->index;
			rdma_put_gid_attr(attr);
			return 0;
		}
		rcu_read_unlock();
		rdma_put_gid_attr(attr);
	}
	return -ENODEV;
}