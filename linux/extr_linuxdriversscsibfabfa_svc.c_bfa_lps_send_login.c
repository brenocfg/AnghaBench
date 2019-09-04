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
struct bfi_lps_login_req_s {int /*<<< orphan*/  mh; int /*<<< orphan*/  auth_en; int /*<<< orphan*/  fdisc; int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  pdu_size; int /*<<< orphan*/  alpa; int /*<<< orphan*/  bfa_tag; } ;
struct bfa_lps_s {int /*<<< orphan*/  qe; int /*<<< orphan*/  reqq; int /*<<< orphan*/  bfa; int /*<<< orphan*/  auth_en; int /*<<< orphan*/  fdisc; int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  pdusz; int /*<<< orphan*/  alpa; int /*<<< orphan*/  bfa_tag; } ;
struct bfa_lps_mod_s {int /*<<< orphan*/  lps_login_q; } ;

/* Variables and functions */
 struct bfa_lps_mod_s* BFA_LPS_MOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BFI_LPS_H2I_LOGIN_REQ ; 
 int /*<<< orphan*/  BFI_MC_LPS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_lps_login_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_lps_send_login(struct bfa_lps_s *lps)
{
	struct bfa_lps_mod_s	*mod = BFA_LPS_MOD(lps->bfa);
	struct bfi_lps_login_req_s	*m;

	m = bfa_reqq_next(lps->bfa, lps->reqq);
	WARN_ON(!m);

	bfi_h2i_set(m->mh, BFI_MC_LPS, BFI_LPS_H2I_LOGIN_REQ,
		bfa_fn_lpu(lps->bfa));

	m->bfa_tag	= lps->bfa_tag;
	m->alpa		= lps->alpa;
	m->pdu_size	= cpu_to_be16(lps->pdusz);
	m->pwwn		= lps->pwwn;
	m->nwwn		= lps->nwwn;
	m->fdisc	= lps->fdisc;
	m->auth_en	= lps->auth_en;

	bfa_reqq_produce(lps->bfa, lps->reqq, m->mh);
	list_del(&lps->qe);
	list_add_tail(&lps->qe, &mod->lps_login_q);
}