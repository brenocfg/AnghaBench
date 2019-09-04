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
struct smc_link {int /*<<< orphan*/  peer_mtu; void* peer_psn; int /*<<< orphan*/  peer_mac; int /*<<< orphan*/  peer_gid; void* peer_qpn; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac; int /*<<< orphan*/  gid; } ;
struct smc_clc_msg_accept_confirm {int /*<<< orphan*/  qp_mtu; int /*<<< orphan*/  psn; TYPE_1__ lcl; int /*<<< orphan*/  qpn; } ;

/* Variables and functions */
 int SMC_GID_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* ntoh24 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smc_link_save_peer_info(struct smc_link *link,
				    struct smc_clc_msg_accept_confirm *clc)
{
	link->peer_qpn = ntoh24(clc->qpn);
	memcpy(link->peer_gid, clc->lcl.gid, SMC_GID_SIZE);
	memcpy(link->peer_mac, clc->lcl.mac, sizeof(link->peer_mac));
	link->peer_psn = ntoh24(clc->psn);
	link->peer_mtu = clc->qp_mtu;
}