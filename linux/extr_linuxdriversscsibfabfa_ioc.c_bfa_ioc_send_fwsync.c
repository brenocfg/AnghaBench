#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfi_ioc_ctrl_req_s {int /*<<< orphan*/  clscode; int /*<<< orphan*/  mh; } ;
struct bfa_mbox_cmd_s {scalar_t__ msg; } ;
struct bfa_ioc_s {int /*<<< orphan*/  clscode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_IOC_H2I_DBG_SYNC ; 
 int /*<<< orphan*/  BFI_MC_IOC ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (struct bfa_ioc_s*,struct bfa_mbox_cmd_s*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_send_fwsync(struct bfa_ioc_s *ioc)
{
	struct bfa_mbox_cmd_s cmd;
	struct bfi_ioc_ctrl_req_s *req = (struct bfi_ioc_ctrl_req_s *) cmd.msg;

	bfi_h2i_set(req->mh, BFI_MC_IOC, BFI_IOC_H2I_DBG_SYNC,
		    bfa_ioc_portid(ioc));
	req->clscode = cpu_to_be16(ioc->clscode);
	bfa_ioc_mbox_queue(ioc, &cmd);
}