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
struct smc_sock {TYPE_1__* clcsock; } ;
struct smc_init_info {int /*<<< orphan*/  ib_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int SMC_CLC_DECL_NOSMCRDEV ; 
 int /*<<< orphan*/  smc_pnet_find_roce_resource (int /*<<< orphan*/ ,struct smc_init_info*) ; 

__attribute__((used)) static int smc_find_rdma_device(struct smc_sock *smc, struct smc_init_info *ini)
{
	/* PNET table look up: search active ib_device and port
	 * within same PNETID that also contains the ethernet device
	 * used for the internal TCP socket
	 */
	smc_pnet_find_roce_resource(smc->clcsock->sk, ini);
	if (!ini->ib_dev)
		return SMC_CLC_DECL_NOSMCRDEV;
	return 0;
}