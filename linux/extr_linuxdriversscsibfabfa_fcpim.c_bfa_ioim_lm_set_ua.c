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
struct bfa_lun_mask_s {scalar_t__ state; int /*<<< orphan*/  ua; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOIM_LM_UA_SET ; 
 scalar_t__ BFA_IOIM_LUN_MASK_ACTIVE ; 
 int MAX_LUN_MASK_CFG ; 
 struct bfa_lun_mask_s* bfa_get_lun_mask_list (struct bfa_s*) ; 

__attribute__((used)) static void
bfa_ioim_lm_set_ua(struct bfa_s *bfa)
{
	struct bfa_lun_mask_s	*lunm_list;
	int	i;

	lunm_list = bfa_get_lun_mask_list(bfa);
	for (i = 0; i < MAX_LUN_MASK_CFG; i++) {
		if (lunm_list[i].state != BFA_IOIM_LUN_MASK_ACTIVE)
			continue;
		lunm_list[i].ua = BFA_IOIM_LM_UA_SET;
	}
}