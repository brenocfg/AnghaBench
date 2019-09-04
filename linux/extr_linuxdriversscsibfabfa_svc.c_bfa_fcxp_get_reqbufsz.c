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
struct bfa_fcxp_s {struct bfa_fcxp_mod_s* fcxp_mod; } ;
struct bfa_fcxp_mod_s {int /*<<< orphan*/  req_pld_sz; } ;

/* Variables and functions */

u32
bfa_fcxp_get_reqbufsz(struct bfa_fcxp_s *fcxp)
{
	struct bfa_fcxp_mod_s *mod = fcxp->fcxp_mod;

	return mod->req_pld_sz;
}