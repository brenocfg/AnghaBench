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
struct smc_ib_device {int /*<<< orphan*/ * mac; int /*<<< orphan*/  ibdev; } ;
struct ib_gid_attr {TYPE_1__* ndev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ IS_ERR (struct ib_gid_attr const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ib_gid_attr* rdma_get_gid_attr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_put_gid_attr (struct ib_gid_attr const*) ; 

__attribute__((used)) static int smc_ib_fill_mac(struct smc_ib_device *smcibdev, u8 ibport)
{
	const struct ib_gid_attr *attr;
	int rc = 0;

	attr = rdma_get_gid_attr(smcibdev->ibdev, ibport, 0);
	if (IS_ERR(attr))
		return -ENODEV;

	if (attr->ndev)
		memcpy(smcibdev->mac[ibport - 1], attr->ndev->dev_addr,
		       ETH_ALEN);
	else
		rc = -ENODEV;

	rdma_put_gid_attr(attr);
	return rc;
}