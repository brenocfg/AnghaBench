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
struct smc_llc_msg_confirm_rkey_cont {TYPE_1__ hd; } ;
struct smc_link {int dummy; } ;

/* Variables and functions */
 int SMC_LLC_FLAG_RESP ; 
 int /*<<< orphan*/  smc_llc_send_message (struct smc_link*,struct smc_llc_msg_confirm_rkey_cont*,int) ; 

__attribute__((used)) static void smc_llc_rx_confirm_rkey_cont(struct smc_link *link,
				      struct smc_llc_msg_confirm_rkey_cont *llc)
{
	if (llc->hd.flags & SMC_LLC_FLAG_RESP) {
		/* unused as long as we don't send this type of msg */
	} else {
		/* ignore rtokens for other links, we have only one link */
		llc->hd.flags |= SMC_LLC_FLAG_RESP;
		smc_llc_send_message(link, llc, sizeof(*llc));
	}
}