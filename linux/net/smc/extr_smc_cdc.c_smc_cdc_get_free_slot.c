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
struct smc_wr_tx_pend_priv {int dummy; } ;
struct smc_wr_buf {int dummy; } ;
struct smc_rdma_wr {int dummy; } ;
struct smc_link {int dummy; } ;
struct smc_connection {int /*<<< orphan*/  alert_token_local; TYPE_1__* lgr; } ;
struct smc_cdc_tx_pend {int dummy; } ;
struct TYPE_2__ {struct smc_link* lnk; } ;

/* Variables and functions */
 int EPIPE ; 
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/  smc_cdc_tx_handler ; 
 int smc_wr_tx_get_free_slot (struct smc_link*,int /*<<< orphan*/ ,struct smc_wr_buf**,struct smc_rdma_wr**,struct smc_wr_tx_pend_priv**) ; 

int smc_cdc_get_free_slot(struct smc_connection *conn,
			  struct smc_wr_buf **wr_buf,
			  struct smc_rdma_wr **wr_rdma_buf,
			  struct smc_cdc_tx_pend **pend)
{
	struct smc_link *link = &conn->lgr->lnk[SMC_SINGLE_LINK];
	int rc;

	rc = smc_wr_tx_get_free_slot(link, smc_cdc_tx_handler, wr_buf,
				     wr_rdma_buf,
				     (struct smc_wr_tx_pend_priv **)pend);
	if (!conn->alert_token_local)
		/* abnormal termination */
		rc = -EPIPE;
	return rc;
}