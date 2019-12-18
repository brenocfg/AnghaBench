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
struct smc_sock {int dummy; } ;
struct smc_init_info {int dummy; } ;

/* Variables and functions */
 int SMC_CLC_DECL_MEM ; 
 scalar_t__ smc_buf_create (struct smc_sock*,int) ; 
 int smc_conn_create (struct smc_sock*,struct smc_init_info*) ; 

__attribute__((used)) static int smc_listen_rdma_init(struct smc_sock *new_smc,
				struct smc_init_info *ini)
{
	int rc;

	/* allocate connection / link group */
	rc = smc_conn_create(new_smc, ini);
	if (rc)
		return rc;

	/* create send buffer and rmb */
	if (smc_buf_create(new_smc, false))
		return SMC_CLC_DECL_MEM;

	return 0;
}