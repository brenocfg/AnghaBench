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
typedef  int /*<<< orphan*/  u8 ;
struct smc_sock {int dummy; } ;
struct smc_ib_device {int dummy; } ;
struct smc_clc_msg_proposal {int /*<<< orphan*/  lcl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SMC_CLC_DECL_INTERR ; 
 int SMC_CLC_DECL_MEM ; 
 scalar_t__ smc_buf_create (struct smc_sock*,int) ; 
 int smc_conn_create (struct smc_sock*,int,int /*<<< orphan*/ ,struct smc_ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_listen_rdma_init(struct smc_sock *new_smc,
				struct smc_clc_msg_proposal *pclc,
				struct smc_ib_device *ibdev, u8 ibport,
				int *local_contact)
{
	/* allocate connection / link group */
	*local_contact = smc_conn_create(new_smc, false, 0, ibdev, ibport,
					 &pclc->lcl, NULL, 0);
	if (*local_contact < 0) {
		if (*local_contact == -ENOMEM)
			return SMC_CLC_DECL_MEM;/* insufficient memory*/
		return SMC_CLC_DECL_INTERR; /* other error */
	}

	/* create send buffer and rmb */
	if (smc_buf_create(new_smc, false))
		return SMC_CLC_DECL_MEM;

	return 0;
}