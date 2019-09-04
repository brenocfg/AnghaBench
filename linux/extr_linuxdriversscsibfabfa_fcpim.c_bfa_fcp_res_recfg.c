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
typedef  int u16 ;
struct list_head {int dummy; } ;
struct bfa_s {int dummy; } ;
struct bfa_fcp_mod_s {int num_ioim_reqs; int max_ioim_reqs; scalar_t__ throttle_update_required; int /*<<< orphan*/  iotag_unused_q; int /*<<< orphan*/  iotag_ioim_free_q; } ;

/* Variables and functions */
 struct bfa_fcp_mod_s* BFA_FCP_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_q_deq_tail (int /*<<< orphan*/ *,struct list_head**) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,int /*<<< orphan*/ *) ; 

void
bfa_fcp_res_recfg(struct bfa_s *bfa, u16 num_ioim_fw, u16 max_ioim_fw)
{
	struct bfa_fcp_mod_s	*mod = BFA_FCP_MOD(bfa);
	struct list_head	*qe;
	int	i;

	/* Update io throttle value only once during driver load time */
	if (!mod->throttle_update_required)
		return;

	for (i = 0; i < (mod->num_ioim_reqs - num_ioim_fw); i++) {
		bfa_q_deq_tail(&mod->iotag_ioim_free_q, &qe);
		list_add_tail(qe, &mod->iotag_unused_q);
	}

	if (mod->num_ioim_reqs != num_ioim_fw) {
		bfa_trc(bfa, mod->num_ioim_reqs);
		bfa_trc(bfa, num_ioim_fw);
	}

	mod->max_ioim_reqs = max_ioim_fw;
	mod->num_ioim_reqs = num_ioim_fw;
	mod->throttle_update_required = 0;
}