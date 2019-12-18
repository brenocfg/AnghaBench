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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int length; int /*<<< orphan*/  add_link_rej_rsn; int /*<<< orphan*/  flags; TYPE_1__ common; } ;
struct smc_llc_msg_add_link {int /*<<< orphan*/  sender_gid; int /*<<< orphan*/  sender_mac; TYPE_2__ hd; } ;
struct smc_link {int dummy; } ;
typedef  enum smc_llc_reqresp { ____Placeholder_smc_llc_reqresp } smc_llc_reqresp ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SMC_GID_SIZE ; 
 int /*<<< orphan*/  SMC_LLC_ADD_LINK ; 
 int /*<<< orphan*/  SMC_LLC_FLAG_ADD_LNK_REJ ; 
 int /*<<< orphan*/  SMC_LLC_FLAG_RESP ; 
 int /*<<< orphan*/  SMC_LLC_REJ_RSN_NO_ALT_PATH ; 
 int SMC_LLC_RESP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct smc_llc_msg_add_link*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smc_llc_prep_add_link(struct smc_llc_msg_add_link *addllc,
				  struct smc_link *link, u8 mac[], u8 gid[],
				  enum smc_llc_reqresp reqresp)
{
	memset(addllc, 0, sizeof(*addllc));
	addllc->hd.common.type = SMC_LLC_ADD_LINK;
	addllc->hd.length = sizeof(struct smc_llc_msg_add_link);
	if (reqresp == SMC_LLC_RESP) {
		addllc->hd.flags |= SMC_LLC_FLAG_RESP;
		/* always reject more links for now */
		addllc->hd.flags |= SMC_LLC_FLAG_ADD_LNK_REJ;
		addllc->hd.add_link_rej_rsn = SMC_LLC_REJ_RSN_NO_ALT_PATH;
	}
	memcpy(addllc->sender_mac, mac, ETH_ALEN);
	memcpy(addllc->sender_gid, gid, SMC_GID_SIZE);
}