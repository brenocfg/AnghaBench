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
struct smc_llc_msg_del_link {TYPE_1__ hd; } ;
struct smc_link_group {scalar_t__ role; } ;
struct smc_link {int dummy; } ;

/* Variables and functions */
 int SMC_LLC_FLAG_RESP ; 
 int /*<<< orphan*/  SMC_LLC_REQ ; 
 int /*<<< orphan*/  SMC_LLC_RESP ; 
 scalar_t__ SMC_SERV ; 
 struct smc_link_group* smc_get_lgr (struct smc_link*) ; 
 int /*<<< orphan*/  smc_lgr_forget (struct smc_link_group*) ; 
 int /*<<< orphan*/  smc_lgr_schedule_free_work_fast (struct smc_link_group*) ; 
 int /*<<< orphan*/  smc_llc_link_deleting (struct smc_link*) ; 
 int /*<<< orphan*/  smc_llc_prep_delete_link (struct smc_llc_msg_del_link*,struct smc_link*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smc_llc_send_message (struct smc_link*,struct smc_llc_msg_del_link*,int) ; 

__attribute__((used)) static void smc_llc_rx_delete_link(struct smc_link *link,
				   struct smc_llc_msg_del_link *llc)
{
	struct smc_link_group *lgr = smc_get_lgr(link);

	if (llc->hd.flags & SMC_LLC_FLAG_RESP) {
		if (lgr->role == SMC_SERV)
			smc_lgr_schedule_free_work_fast(lgr);
	} else {
		smc_lgr_forget(lgr);
		smc_llc_link_deleting(link);
		if (lgr->role == SMC_SERV) {
			/* client asks to delete this link, send request */
			smc_llc_prep_delete_link(llc, link, SMC_LLC_REQ, true);
		} else {
			/* server requests to delete this link, send response */
			smc_llc_prep_delete_link(llc, link, SMC_LLC_RESP, true);
		}
		smc_llc_send_message(link, llc, sizeof(*llc));
		smc_lgr_schedule_free_work_fast(lgr);
	}
}