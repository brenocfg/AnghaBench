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
struct bfi_ioc_ctrl_req_s {int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  clscode; int /*<<< orphan*/  mh; } ;
struct bfa_ioc_s {int /*<<< orphan*/  clscode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_IOC_H2I_ENABLE_REQ ; 
 int /*<<< orphan*/  BFI_MC_IOC ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_send (struct bfa_ioc_s*,struct bfi_ioc_ctrl_req_s*,int) ; 
 int /*<<< orphan*/  bfa_ioc_portid (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 

__attribute__((used)) static void
bfa_ioc_send_enable(struct bfa_ioc_s *ioc)
{
	struct bfi_ioc_ctrl_req_s enable_req;

	bfi_h2i_set(enable_req.mh, BFI_MC_IOC, BFI_IOC_H2I_ENABLE_REQ,
		    bfa_ioc_portid(ioc));
	enable_req.clscode = cpu_to_be16(ioc->clscode);
	/* unsigned 32-bit time_t overflow in y2106 */
	enable_req.tv_sec = be32_to_cpu(ktime_get_real_seconds());
	bfa_ioc_mbox_send(ioc, &enable_req, sizeof(struct bfi_ioc_ctrl_req_s));
}