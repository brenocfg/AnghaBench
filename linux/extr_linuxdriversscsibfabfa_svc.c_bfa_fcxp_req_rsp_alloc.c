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
struct bfa_s {int dummy; } ;
struct bfa_fcxp_s {int /*<<< orphan*/  fcxp_tag; } ;
typedef  int /*<<< orphan*/  bfa_fcxp_get_sglen_t ;
typedef  int /*<<< orphan*/  bfa_fcxp_get_sgaddr_t ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCXP_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct bfa_fcxp_s* bfa_fcxp_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcxp_init (struct bfa_fcxp_s*,void*,struct bfa_s*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int /*<<< orphan*/ ) ; 

struct bfa_fcxp_s *
bfa_fcxp_req_rsp_alloc(void *caller, struct bfa_s *bfa, int nreq_sgles,
		int nrsp_sgles, bfa_fcxp_get_sgaddr_t req_sga_cbfn,
		bfa_fcxp_get_sglen_t req_sglen_cbfn,
		bfa_fcxp_get_sgaddr_t rsp_sga_cbfn,
		bfa_fcxp_get_sglen_t rsp_sglen_cbfn, bfa_boolean_t req)
{
	struct bfa_fcxp_s *fcxp = NULL;

	WARN_ON(bfa == NULL);

	fcxp = bfa_fcxp_get(BFA_FCXP_MOD(bfa), req);
	if (fcxp == NULL)
		return NULL;

	bfa_trc(bfa, fcxp->fcxp_tag);

	bfa_fcxp_init(fcxp, caller, bfa, nreq_sgles, nrsp_sgles, req_sga_cbfn,
			req_sglen_cbfn, rsp_sga_cbfn, rsp_sglen_cbfn);

	return fcxp;
}