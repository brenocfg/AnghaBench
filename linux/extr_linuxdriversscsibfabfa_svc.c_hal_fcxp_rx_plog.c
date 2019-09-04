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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bfi_fcxp_send_rsp_s {scalar_t__ rsp_len; int /*<<< orphan*/  fchs; } ;
struct bfa_s {int /*<<< orphan*/  plog; } ;
struct bfa_fcxp_s {scalar_t__ use_irspbuf; } ;

/* Variables and functions */
 scalar_t__ BFA_FCXP_RSP_PLD (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  BFA_PL_EID_RX ; 
 int /*<<< orphan*/  BFA_PL_MID_HAL_FCXP ; 
 int /*<<< orphan*/  bfa_plog_fchdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_plog_fchdr_and_pl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hal_fcxp_rx_plog(struct bfa_s *bfa, struct bfa_fcxp_s *fcxp,
		 struct bfi_fcxp_send_rsp_s *fcxp_rsp)
{
	if (fcxp_rsp->rsp_len > 0) {
		if (fcxp->use_irspbuf) {
			u32	pld_w0 =
				*((u32 *) BFA_FCXP_RSP_PLD(fcxp));

			bfa_plog_fchdr_and_pl(bfa->plog, BFA_PL_MID_HAL_FCXP,
					      BFA_PL_EID_RX,
					      (u16) fcxp_rsp->rsp_len,
					      &fcxp_rsp->fchs, pld_w0);
		} else {
			bfa_plog_fchdr(bfa->plog, BFA_PL_MID_HAL_FCXP,
				       BFA_PL_EID_RX,
				       (u16) fcxp_rsp->rsp_len,
				       &fcxp_rsp->fchs);
		}
	} else {
		bfa_plog_fchdr(bfa->plog, BFA_PL_MID_HAL_FCXP, BFA_PL_EID_RX,
			       (u16) fcxp_rsp->rsp_len, &fcxp_rsp->fchs);
	}
}