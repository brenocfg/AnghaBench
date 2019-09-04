#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ submod_enabled; } ;
struct bfa_s {TYPE_1__ iocfc; } ;

/* Variables and functions */
 scalar_t__ BFA_FALSE ; 
 int /*<<< orphan*/  bfa_dconf_iocdisable (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcdiag_iocdisable (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcp_iocdisable (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcport_iocdisable (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_iocdisable (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_lps_iocdisable (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_rport_iocdisable (struct bfa_s*) ; 

__attribute__((used)) static void
bfa_iocfc_disable_submod(struct bfa_s *bfa)
{
	if (bfa->iocfc.submod_enabled == BFA_FALSE)
		return;

	bfa_fcdiag_iocdisable(bfa);
	bfa_fcport_iocdisable(bfa);
	bfa_fcxp_iocdisable(bfa);
	bfa_lps_iocdisable(bfa);
	bfa_rport_iocdisable(bfa);
	bfa_fcp_iocdisable(bfa);
	bfa_dconf_iocdisable(bfa);

	bfa->iocfc.submod_enabled = BFA_FALSE;
}