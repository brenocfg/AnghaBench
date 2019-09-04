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
typedef  int u32 ;
struct __qm_mc_cgr {int /*<<< orphan*/  cscn_targ; int /*<<< orphan*/  cscn_targ_upd_ctrl; } ;

/* Variables and functions */
 scalar_t__ QMAN_REV30 ; 
 int QM_CGR_TARG_PORTAL (int) ; 
 int QM_CGR_TARG_UDP_CTRL_WRITE_BIT ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 scalar_t__ qman_ip_rev ; 

__attribute__((used)) static void qm_cgr_cscn_targ_set(struct __qm_mc_cgr *cgr, int pi, u32 val)
{
	if (qman_ip_rev >= QMAN_REV30)
		cgr->cscn_targ_upd_ctrl = cpu_to_be16(pi |
					QM_CGR_TARG_UDP_CTRL_WRITE_BIT);
	else
		cgr->cscn_targ = cpu_to_be32(val | QM_CGR_TARG_PORTAL(pi));
}