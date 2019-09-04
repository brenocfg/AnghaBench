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
struct smc_wr_tx_pend_priv {int dummy; } ;
struct smc_wr_buf {int dummy; } ;
struct smc_llc_msg_add_link {int dummy; } ;
struct smc_link {int dummy; } ;
typedef  enum smc_llc_reqresp { ____Placeholder_smc_llc_reqresp } smc_llc_reqresp ;

/* Variables and functions */
 int smc_llc_add_pending_send (struct smc_link*,struct smc_wr_buf**,struct smc_wr_tx_pend_priv**) ; 
 int /*<<< orphan*/  smc_llc_prep_add_link (struct smc_llc_msg_add_link*,struct smc_link*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int smc_wr_tx_send (struct smc_link*,struct smc_wr_tx_pend_priv*) ; 

int smc_llc_send_add_link(struct smc_link *link, u8 mac[], u8 gid[],
			  enum smc_llc_reqresp reqresp)
{
	struct smc_llc_msg_add_link *addllc;
	struct smc_wr_tx_pend_priv *pend;
	struct smc_wr_buf *wr_buf;
	int rc;

	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	if (rc)
		return rc;
	addllc = (struct smc_llc_msg_add_link *)wr_buf;
	smc_llc_prep_add_link(addllc, link, mac, gid, reqresp);
	/* send llc message */
	rc = smc_wr_tx_send(link, pend);
	return rc;
}