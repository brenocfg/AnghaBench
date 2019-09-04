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
typedef  int /*<<< orphan*/  u32 ;
struct bfi_diag_portbeacon_req_s {int /*<<< orphan*/  period; int /*<<< orphan*/  beacon; int /*<<< orphan*/  mh; } ;
struct TYPE_4__ {scalar_t__ msg; } ;
struct TYPE_3__ {TYPE_2__ mbcmd; } ;
struct bfa_diag_s {TYPE_1__ beacon; int /*<<< orphan*/  ioc; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_DIAG_H2I_PORTBEACON ; 
 int /*<<< orphan*/  BFI_MC_DIAG ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
diag_portbeacon_send(struct bfa_diag_s *diag, bfa_boolean_t beacon, u32 sec)
{
	struct bfi_diag_portbeacon_req_s *msg;

	msg = (struct bfi_diag_portbeacon_req_s *)diag->beacon.mbcmd.msg;
	/* build host command */
	bfi_h2i_set(msg->mh, BFI_MC_DIAG, BFI_DIAG_H2I_PORTBEACON,
		bfa_ioc_portid(diag->ioc));
	msg->beacon = beacon;
	msg->period = cpu_to_be32(sec);
	/* send mbox cmd */
	bfa_ioc_mbox_queue(diag->ioc, &diag->beacon.mbcmd);
}