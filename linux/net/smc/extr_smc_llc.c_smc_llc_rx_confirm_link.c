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
struct TYPE_2__ {int flags; } ;
struct smc_llc_msg_confirm_link {int /*<<< orphan*/  link_num; TYPE_1__ hd; } ;
struct smc_link_group {scalar_t__ role; } ;
struct smc_link {scalar_t__ state; int llc_confirm_resp_rc; int llc_confirm_rc; int /*<<< orphan*/  llc_confirm; int /*<<< orphan*/  link_id; int /*<<< orphan*/  llc_confirm_resp; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ SMC_CLNT ; 
 int SMC_LLC_FLAG_NO_RMBE_EYEC ; 
 int SMC_LLC_FLAG_RESP ; 
 scalar_t__ SMC_LNK_ACTIVATING ; 
 scalar_t__ SMC_SERV ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct smc_link_group* smc_get_lgr (struct smc_link*) ; 

__attribute__((used)) static void smc_llc_rx_confirm_link(struct smc_link *link,
				    struct smc_llc_msg_confirm_link *llc)
{
	struct smc_link_group *lgr = smc_get_lgr(link);
	int conf_rc;

	/* RMBE eyecatchers are not supported */
	if (llc->hd.flags & SMC_LLC_FLAG_NO_RMBE_EYEC)
		conf_rc = 0;
	else
		conf_rc = ENOTSUPP;

	if (llc->hd.flags & SMC_LLC_FLAG_RESP) {
		if (lgr->role == SMC_SERV &&
		    link->state == SMC_LNK_ACTIVATING) {
			link->llc_confirm_resp_rc = conf_rc;
			complete(&link->llc_confirm_resp);
		}
	} else {
		if (lgr->role == SMC_CLNT &&
		    link->state == SMC_LNK_ACTIVATING) {
			link->llc_confirm_rc = conf_rc;
			link->link_id = llc->link_num;
			complete(&link->llc_confirm);
		}
	}
}