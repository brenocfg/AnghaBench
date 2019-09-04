#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct smc_wr_tx_pend_priv {int dummy; } ;
struct smc_wr_buf {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int length; TYPE_1__ common; } ;
struct smc_llc_msg_confirm_rkey {TYPE_4__* rtoken; TYPE_2__ hd; } ;
struct smc_link {int dummy; } ;
struct smc_buf_desc {TYPE_5__* sgt; TYPE_3__** mr_rx; } ;
struct TYPE_10__ {int /*<<< orphan*/  sgl; } ;
struct TYPE_9__ {int /*<<< orphan*/  rmb_vaddr; int /*<<< orphan*/  rmb_key; } ;
struct TYPE_8__ {int /*<<< orphan*/  rkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_LLC_CONFIRM_RKEY ; 
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct smc_llc_msg_confirm_rkey*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sg_dma_address (int /*<<< orphan*/ ) ; 
 int smc_llc_add_pending_send (struct smc_link*,struct smc_wr_buf**,struct smc_wr_tx_pend_priv**) ; 
 int smc_wr_tx_send (struct smc_link*,struct smc_wr_tx_pend_priv*) ; 

__attribute__((used)) static int smc_llc_send_confirm_rkey(struct smc_link *link,
				     struct smc_buf_desc *rmb_desc)
{
	struct smc_llc_msg_confirm_rkey *rkeyllc;
	struct smc_wr_tx_pend_priv *pend;
	struct smc_wr_buf *wr_buf;
	int rc;

	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	if (rc)
		return rc;
	rkeyllc = (struct smc_llc_msg_confirm_rkey *)wr_buf;
	memset(rkeyllc, 0, sizeof(*rkeyllc));
	rkeyllc->hd.common.type = SMC_LLC_CONFIRM_RKEY;
	rkeyllc->hd.length = sizeof(struct smc_llc_msg_confirm_rkey);
	rkeyllc->rtoken[0].rmb_key =
		htonl(rmb_desc->mr_rx[SMC_SINGLE_LINK]->rkey);
	rkeyllc->rtoken[0].rmb_vaddr = cpu_to_be64(
		(u64)sg_dma_address(rmb_desc->sgt[SMC_SINGLE_LINK].sgl));
	/* send llc message */
	rc = smc_wr_tx_send(link, pend);
	return rc;
}