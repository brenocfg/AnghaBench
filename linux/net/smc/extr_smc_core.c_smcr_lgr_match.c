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
typedef  scalar_t__ u32 ;
struct smc_link_group {int role; TYPE_1__* lnk; int /*<<< orphan*/  peer_systemid; } ;
struct smc_clc_msg_local {int /*<<< orphan*/ * mac; int /*<<< orphan*/  gid; int /*<<< orphan*/ * id_for_peer; } ;
typedef  enum smc_lgr_role { ____Placeholder_smc_lgr_role } smc_lgr_role ;
struct TYPE_2__ {scalar_t__ peer_qpn; int /*<<< orphan*/  peer_mac; int /*<<< orphan*/  peer_gid; } ;

/* Variables and functions */
 int SMC_GID_SIZE ; 
 scalar_t__ SMC_SERV ; 
 size_t SMC_SINGLE_LINK ; 
 int SMC_SYSTEMID_LEN ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool smcr_lgr_match(struct smc_link_group *lgr,
			   struct smc_clc_msg_local *lcl,
			   enum smc_lgr_role role, u32 clcqpn)
{
	return !memcmp(lgr->peer_systemid, lcl->id_for_peer,
		       SMC_SYSTEMID_LEN) &&
		!memcmp(lgr->lnk[SMC_SINGLE_LINK].peer_gid, &lcl->gid,
			SMC_GID_SIZE) &&
		!memcmp(lgr->lnk[SMC_SINGLE_LINK].peer_mac, lcl->mac,
			sizeof(lcl->mac)) &&
		lgr->role == role &&
		(lgr->role == SMC_SERV ||
		 lgr->lnk[SMC_SINGLE_LINK].peer_qpn == clcqpn);
}