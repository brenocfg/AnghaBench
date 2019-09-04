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
struct TYPE_4__ {int flags; } ;
struct smc_llc_msg_confirm_rkey {TYPE_2__ hd; TYPE_1__* rtoken; } ;
struct smc_link {int llc_confirm_rkey_rc; int /*<<< orphan*/  llc_confirm_rkey; } ;
struct TYPE_3__ {int /*<<< orphan*/  rmb_key; int /*<<< orphan*/  rmb_vaddr; } ;

/* Variables and functions */
 int SMC_LLC_FLAG_RESP ; 
 int SMC_LLC_FLAG_RKEY_NEG ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_get_lgr (struct smc_link*) ; 
 int /*<<< orphan*/  smc_llc_send_message (struct smc_link*,struct smc_llc_msg_confirm_rkey*,int) ; 
 int smc_rtoken_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smc_llc_rx_confirm_rkey(struct smc_link *link,
				    struct smc_llc_msg_confirm_rkey *llc)
{
	int rc;

	if (llc->hd.flags & SMC_LLC_FLAG_RESP) {
		link->llc_confirm_rkey_rc = llc->hd.flags &
					    SMC_LLC_FLAG_RKEY_NEG;
		complete(&link->llc_confirm_rkey);
	} else {
		rc = smc_rtoken_add(smc_get_lgr(link),
				    llc->rtoken[0].rmb_vaddr,
				    llc->rtoken[0].rmb_key);

		/* ignore rtokens for other links, we have only one link */

		llc->hd.flags |= SMC_LLC_FLAG_RESP;
		if (rc < 0)
			llc->hd.flags |= SMC_LLC_FLAG_RKEY_NEG;
		smc_llc_send_message(link, llc, sizeof(*llc));
	}
}