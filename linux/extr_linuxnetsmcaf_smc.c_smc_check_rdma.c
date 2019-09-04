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
typedef  int /*<<< orphan*/  u8 ;
struct smc_sock {TYPE_1__* clcsock; } ;
struct smc_ib_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int SMC_CLC_DECL_CNFERR ; 
 int /*<<< orphan*/  smc_pnet_find_roce_resource (int /*<<< orphan*/ ,struct smc_ib_device**,int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smc_check_rdma(struct smc_sock *smc, struct smc_ib_device **ibdev,
			  u8 *ibport, unsigned short vlan_id, u8 gid[])
{
	int reason_code = 0;

	/* PNET table look up: search active ib_device and port
	 * within same PNETID that also contains the ethernet device
	 * used for the internal TCP socket
	 */
	smc_pnet_find_roce_resource(smc->clcsock->sk, ibdev, ibport, vlan_id,
				    gid);
	if (!(*ibdev))
		reason_code = SMC_CLC_DECL_CNFERR; /* configuration error */

	return reason_code;
}