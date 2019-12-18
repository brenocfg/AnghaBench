#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct smc_wr_tx_pend_priv {int dummy; } ;
struct smc_wr_buf {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int length; int /*<<< orphan*/  flags; TYPE_1__ common; } ;
struct smc_llc_msg_confirm_link {int /*<<< orphan*/  max_links; int /*<<< orphan*/  link_uid; int /*<<< orphan*/  link_num; int /*<<< orphan*/  sender_qp_num; int /*<<< orphan*/  sender_gid; int /*<<< orphan*/  sender_mac; TYPE_2__ hd; } ;
struct smc_link_group {int /*<<< orphan*/  id; } ;
struct smc_link {int ibport; int /*<<< orphan*/  link_id; TYPE_4__* roce_qp; int /*<<< orphan*/  gid; TYPE_3__* smcibdev; } ;
typedef  enum smc_llc_reqresp { ____Placeholder_smc_llc_reqresp } smc_llc_reqresp ;
struct TYPE_8__ {int /*<<< orphan*/  qp_num; } ;
struct TYPE_7__ {int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SMC_GID_SIZE ; 
 int /*<<< orphan*/  SMC_LGR_ID_SIZE ; 
 int /*<<< orphan*/  SMC_LLC_ADD_LNK_MAX_LINKS ; 
 int /*<<< orphan*/  SMC_LLC_CONFIRM_LINK ; 
 int /*<<< orphan*/  SMC_LLC_FLAG_NO_RMBE_EYEC ; 
 int /*<<< orphan*/  SMC_LLC_FLAG_RESP ; 
 int SMC_LLC_RESP ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct smc_llc_msg_confirm_link*,int /*<<< orphan*/ ,int) ; 
 struct smc_link_group* smc_get_lgr (struct smc_link*) ; 
 int smc_llc_add_pending_send (struct smc_link*,struct smc_wr_buf**,struct smc_wr_tx_pend_priv**) ; 
 int smc_wr_tx_send (struct smc_link*,struct smc_wr_tx_pend_priv*) ; 

int smc_llc_send_confirm_link(struct smc_link *link,
			      enum smc_llc_reqresp reqresp)
{
	struct smc_link_group *lgr = smc_get_lgr(link);
	struct smc_llc_msg_confirm_link *confllc;
	struct smc_wr_tx_pend_priv *pend;
	struct smc_wr_buf *wr_buf;
	int rc;

	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	if (rc)
		return rc;
	confllc = (struct smc_llc_msg_confirm_link *)wr_buf;
	memset(confllc, 0, sizeof(*confllc));
	confllc->hd.common.type = SMC_LLC_CONFIRM_LINK;
	confllc->hd.length = sizeof(struct smc_llc_msg_confirm_link);
	confllc->hd.flags |= SMC_LLC_FLAG_NO_RMBE_EYEC;
	if (reqresp == SMC_LLC_RESP)
		confllc->hd.flags |= SMC_LLC_FLAG_RESP;
	memcpy(confllc->sender_mac, link->smcibdev->mac[link->ibport - 1],
	       ETH_ALEN);
	memcpy(confllc->sender_gid, link->gid, SMC_GID_SIZE);
	hton24(confllc->sender_qp_num, link->roce_qp->qp_num);
	confllc->link_num = link->link_id;
	memcpy(confllc->link_uid, lgr->id, SMC_LGR_ID_SIZE);
	confllc->max_links = SMC_LLC_ADD_LNK_MAX_LINKS; /* enforce peer resp. */
	/* send llc message */
	rc = smc_wr_tx_send(link, pend);
	return rc;
}