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
struct TYPE_3__ {int flags; } ;
struct smc_llc_msg_add_link {TYPE_1__ hd; } ;
struct smc_link_group {scalar_t__ role; } ;
struct smc_link {scalar_t__ state; int ibport; int /*<<< orphan*/  gid; TYPE_2__* smcibdev; int /*<<< orphan*/  llc_add; int /*<<< orphan*/  llc_add_resp; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
 int SMC_LLC_FLAG_RESP ; 
 int /*<<< orphan*/  SMC_LLC_REQ ; 
 int /*<<< orphan*/  SMC_LLC_RESP ; 
 scalar_t__ SMC_LNK_ACTIVATING ; 
 scalar_t__ SMC_SERV ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct smc_link_group* smc_get_lgr (struct smc_link*) ; 
 int /*<<< orphan*/  smc_llc_prep_add_link (struct smc_llc_msg_add_link*,struct smc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_llc_send_message (struct smc_link*,struct smc_llc_msg_add_link*,int) ; 

__attribute__((used)) static void smc_llc_rx_add_link(struct smc_link *link,
				struct smc_llc_msg_add_link *llc)
{
	struct smc_link_group *lgr = smc_get_lgr(link);

	if (llc->hd.flags & SMC_LLC_FLAG_RESP) {
		if (link->state == SMC_LNK_ACTIVATING)
			complete(&link->llc_add_resp);
	} else {
		if (link->state == SMC_LNK_ACTIVATING) {
			complete(&link->llc_add);
			return;
		}

		if (lgr->role == SMC_SERV) {
			smc_llc_prep_add_link(llc, link,
					link->smcibdev->mac[link->ibport - 1],
					link->gid, SMC_LLC_REQ);

		} else {
			smc_llc_prep_add_link(llc, link,
					link->smcibdev->mac[link->ibport - 1],
					link->gid, SMC_LLC_RESP);
		}
		smc_llc_send_message(link, llc, sizeof(*llc));
	}
}