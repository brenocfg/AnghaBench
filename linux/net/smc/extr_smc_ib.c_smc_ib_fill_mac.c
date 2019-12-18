#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct smc_ib_device {int /*<<< orphan*/ * mac; int /*<<< orphan*/  ibdev; } ;
struct ib_gid_attr {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct ib_gid_attr const*) ; 
 struct ib_gid_attr* rdma_get_gid_attr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_put_gid_attr (struct ib_gid_attr const*) ; 
 int rdma_read_gid_l2_fields (struct ib_gid_attr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_ib_fill_mac(struct smc_ib_device *smcibdev, u8 ibport)
{
	const struct ib_gid_attr *attr;
	int rc;

	attr = rdma_get_gid_attr(smcibdev->ibdev, ibport, 0);
	if (IS_ERR(attr))
		return -ENODEV;

	rc = rdma_read_gid_l2_fields(attr, NULL, smcibdev->mac[ibport - 1]);
	rdma_put_gid_attr(attr);
	return rc;
}