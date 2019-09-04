#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smc_wr_tx_pend_priv {int dummy; } ;
struct smc_wr_buf {int dummy; } ;
struct smc_link {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cons; scalar_t__ seqno; } ;
struct smc_connection {TYPE_2__ local_tx_ctrl; int /*<<< orphan*/  rx_curs_confirmed; scalar_t__ tx_cdc_seq; TYPE_1__* lgr; } ;
struct smc_cdc_tx_pend {int dummy; } ;
struct smc_cdc_msg {int dummy; } ;
struct TYPE_3__ {struct smc_link* lnk; } ;

/* Variables and functions */
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/  smc_cdc_add_pending_send (struct smc_connection*,struct smc_cdc_tx_pend*) ; 
 int /*<<< orphan*/  smc_curs_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct smc_connection*) ; 
 int /*<<< orphan*/  smc_host_msg_to_cdc (struct smc_cdc_msg*,TYPE_2__*,struct smc_connection*) ; 
 int smc_wr_tx_send (struct smc_link*,struct smc_wr_tx_pend_priv*) ; 

int smc_cdc_msg_send(struct smc_connection *conn,
		     struct smc_wr_buf *wr_buf,
		     struct smc_cdc_tx_pend *pend)
{
	struct smc_link *link;
	int rc;

	link = &conn->lgr->lnk[SMC_SINGLE_LINK];

	smc_cdc_add_pending_send(conn, pend);

	conn->tx_cdc_seq++;
	conn->local_tx_ctrl.seqno = conn->tx_cdc_seq;
	smc_host_msg_to_cdc((struct smc_cdc_msg *)wr_buf,
			    &conn->local_tx_ctrl, conn);
	rc = smc_wr_tx_send(link, (struct smc_wr_tx_pend_priv *)pend);
	if (!rc)
		smc_curs_copy(&conn->rx_curs_confirmed,
			      &conn->local_tx_ctrl.cons, conn);

	return rc;
}