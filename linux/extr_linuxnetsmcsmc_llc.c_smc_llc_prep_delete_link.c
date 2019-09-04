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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int length; int /*<<< orphan*/  flags; TYPE_1__ common; } ;
struct smc_llc_msg_del_link {int /*<<< orphan*/  link_num; TYPE_2__ hd; } ;
struct smc_llc_msg_add_link {int dummy; } ;
struct smc_link {int /*<<< orphan*/  link_id; } ;
typedef  enum smc_llc_reqresp { ____Placeholder_smc_llc_reqresp } smc_llc_reqresp ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_LLC_DELETE_LINK ; 
 int /*<<< orphan*/  SMC_LLC_FLAG_DEL_LINK_ALL ; 
 int /*<<< orphan*/  SMC_LLC_FLAG_DEL_LINK_ORDERLY ; 
 int /*<<< orphan*/  SMC_LLC_FLAG_RESP ; 
 int SMC_LLC_RESP ; 
 int /*<<< orphan*/  memset (struct smc_llc_msg_del_link*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smc_llc_prep_delete_link(struct smc_llc_msg_del_link *delllc,
				     struct smc_link *link,
				     enum smc_llc_reqresp reqresp, bool orderly)
{
	memset(delllc, 0, sizeof(*delllc));
	delllc->hd.common.type = SMC_LLC_DELETE_LINK;
	delllc->hd.length = sizeof(struct smc_llc_msg_add_link);
	if (reqresp == SMC_LLC_RESP)
		delllc->hd.flags |= SMC_LLC_FLAG_RESP;
	/* DEL_LINK_ALL because only 1 link supported */
	delllc->hd.flags |= SMC_LLC_FLAG_DEL_LINK_ALL;
	if (orderly)
		delllc->hd.flags |= SMC_LLC_FLAG_DEL_LINK_ORDERLY;
	delllc->link_num = link->link_id;
}