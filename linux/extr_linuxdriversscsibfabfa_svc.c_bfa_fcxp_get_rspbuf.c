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
typedef  void u8 ;
struct bfa_fcxp_s {int use_irspbuf; int /*<<< orphan*/  fcxp_tag; struct bfa_fcxp_mod_s* fcxp_mod; } ;
struct bfa_fcxp_mod_s {int req_pld_sz; int rsp_pld_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* bfa_mem_get_dmabuf_kva (struct bfa_fcxp_mod_s*,int /*<<< orphan*/ ,int) ; 

void *
bfa_fcxp_get_rspbuf(struct bfa_fcxp_s *fcxp)
{
	struct bfa_fcxp_mod_s *mod = fcxp->fcxp_mod;
	void	*fcxp_buf;

	WARN_ON(fcxp->use_irspbuf != 1);

	fcxp_buf = bfa_mem_get_dmabuf_kva(mod, fcxp->fcxp_tag,
				mod->req_pld_sz + mod->rsp_pld_sz);

	/* fcxp_buf = req_buf + rsp_buf :- add req_buf_sz to get to rsp_buf */
	return ((u8 *) fcxp_buf) + mod->req_pld_sz;
}