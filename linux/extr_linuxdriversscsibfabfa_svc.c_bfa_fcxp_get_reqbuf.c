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
struct bfa_fcxp_s {int use_ireqbuf; int /*<<< orphan*/  fcxp_tag; struct bfa_fcxp_mod_s* fcxp_mod; } ;
struct bfa_fcxp_mod_s {scalar_t__ rsp_pld_sz; scalar_t__ req_pld_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* bfa_mem_get_dmabuf_kva (struct bfa_fcxp_mod_s*,int /*<<< orphan*/ ,scalar_t__) ; 

void *
bfa_fcxp_get_reqbuf(struct bfa_fcxp_s *fcxp)
{
	struct bfa_fcxp_mod_s *mod = fcxp->fcxp_mod;
	void	*reqbuf;

	WARN_ON(fcxp->use_ireqbuf != 1);
	reqbuf = bfa_mem_get_dmabuf_kva(mod, fcxp->fcxp_tag,
				mod->req_pld_sz + mod->rsp_pld_sz);
	return reqbuf;
}