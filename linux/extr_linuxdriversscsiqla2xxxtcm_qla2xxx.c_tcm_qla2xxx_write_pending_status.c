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
struct se_cmd {scalar_t__ t_state; int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  t_transport_stop_comp; } ;

/* Variables and functions */
 scalar_t__ TRANSPORT_COMPLETE_QF_WP ; 
 scalar_t__ TRANSPORT_WRITE_PENDING ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tcm_qla2xxx_write_pending_status(struct se_cmd *se_cmd)
{
	unsigned long flags;
	/*
	 * Check for WRITE_PENDING status to determine if we need to wait for
	 * CTIO aborts to be posted via hardware in tcm_qla2xxx_handle_data().
	 */
	spin_lock_irqsave(&se_cmd->t_state_lock, flags);
	if (se_cmd->t_state == TRANSPORT_WRITE_PENDING ||
	    se_cmd->t_state == TRANSPORT_COMPLETE_QF_WP) {
		spin_unlock_irqrestore(&se_cmd->t_state_lock, flags);
		wait_for_completion_timeout(&se_cmd->t_transport_stop_comp,
						50);
		return 0;
	}
	spin_unlock_irqrestore(&se_cmd->t_state_lock, flags);

	return 0;
}