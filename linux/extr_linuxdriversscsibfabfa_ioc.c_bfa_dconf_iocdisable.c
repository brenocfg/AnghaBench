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
struct bfa_dconf_mod_s {int dummy; } ;

/* Variables and functions */
 struct bfa_dconf_mod_s* BFA_DCONF_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  BFA_DCONF_SM_IOCDISABLE ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_dconf_mod_s*,int /*<<< orphan*/ ) ; 

void
bfa_dconf_iocdisable(struct bfa_s *bfa)
{
	struct bfa_dconf_mod_s *dconf = BFA_DCONF_MOD(bfa);
	bfa_sm_send_event(dconf, BFA_DCONF_SM_IOCDISABLE);
}