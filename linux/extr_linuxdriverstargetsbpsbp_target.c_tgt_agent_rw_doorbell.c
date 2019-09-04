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
struct sbp_target_agent {int doorbell; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGENT_STATE_ACTIVE ; 
 int /*<<< orphan*/  AGENT_STATE_SUSPENDED ; 
 int RCODE_COMPLETE ; 
 int RCODE_CONFLICT_ERROR ; 
 int RCODE_TYPE_ERROR ; 
#define  TCODE_READ_QUADLET_REQUEST 129 
#define  TCODE_WRITE_QUADLET_REQUEST 128 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 

__attribute__((used)) static int tgt_agent_rw_doorbell(struct fw_card *card, int tcode, void *data,
		struct sbp_target_agent *agent)
{
	switch (tcode) {
	case TCODE_WRITE_QUADLET_REQUEST:
		spin_lock_bh(&agent->lock);
		if (agent->state != AGENT_STATE_SUSPENDED) {
			spin_unlock_bh(&agent->lock);
			pr_debug("Ignoring DOORBELL while active.\n");
			return RCODE_CONFLICT_ERROR;
		}
		agent->state = AGENT_STATE_ACTIVE;
		spin_unlock_bh(&agent->lock);

		agent->doorbell = true;

		pr_debug("tgt_agent DOORBELL\n");

		queue_work(system_unbound_wq, &agent->work);

		return RCODE_COMPLETE;

	case TCODE_READ_QUADLET_REQUEST:
		return RCODE_COMPLETE;

	default:
		return RCODE_TYPE_ERROR;
	}
}