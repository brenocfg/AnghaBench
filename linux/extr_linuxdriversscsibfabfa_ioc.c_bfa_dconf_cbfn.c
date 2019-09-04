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
struct bfa_dconf_mod_s {int dummy; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DCONF_SM_FLASH_COMP ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_dconf_mod_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_dconf_cbfn(void *arg, bfa_status_t status)
{
	struct bfa_dconf_mod_s *dconf = arg;
	WARN_ON(status);
	bfa_sm_send_event(dconf, BFA_DCONF_SM_FLASH_COMP);
}