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
struct bfa_fcxp_s {int /*<<< orphan*/  rsp_fchs; int /*<<< orphan*/  residue_len; int /*<<< orphan*/  rsp_len; int /*<<< orphan*/  rsp_status; int /*<<< orphan*/  send_cbarg; int /*<<< orphan*/  caller; int /*<<< orphan*/  (* send_cbfn ) (int /*<<< orphan*/ ,struct bfa_fcxp_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcxp_free (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bfa_fcxp_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__bfa_fcxp_send_cbfn(void *cbarg, bfa_boolean_t complete)
{
	struct bfa_fcxp_s *fcxp = cbarg;

	if (complete) {
		fcxp->send_cbfn(fcxp->caller, fcxp, fcxp->send_cbarg,
				fcxp->rsp_status, fcxp->rsp_len,
				fcxp->residue_len, &fcxp->rsp_fchs);
	} else {
		bfa_fcxp_free(fcxp);
	}
}