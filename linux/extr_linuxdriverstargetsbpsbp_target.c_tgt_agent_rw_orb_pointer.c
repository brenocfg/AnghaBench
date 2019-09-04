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
struct sbp_target_agent {int doorbell; int /*<<< orphan*/  lock; int /*<<< orphan*/  orb_pointer; int /*<<< orphan*/  work; int /*<<< orphan*/  state; } ;
struct sbp2_pointer {int dummy; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGENT_STATE_ACTIVE ; 
 int /*<<< orphan*/  AGENT_STATE_RESET ; 
 int /*<<< orphan*/  AGENT_STATE_SUSPENDED ; 
 int RCODE_COMPLETE ; 
 int RCODE_CONFLICT_ERROR ; 
 int RCODE_TYPE_ERROR ; 
#define  TCODE_READ_BLOCK_REQUEST 129 
#define  TCODE_WRITE_BLOCK_REQUEST 128 
 int /*<<< orphan*/  addr_to_sbp2_pointer (int /*<<< orphan*/ ,struct sbp2_pointer*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbp2_pointer_to_addr (struct sbp2_pointer*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 

__attribute__((used)) static int tgt_agent_rw_orb_pointer(struct fw_card *card, int tcode, void *data,
		struct sbp_target_agent *agent)
{
	struct sbp2_pointer *ptr = data;

	switch (tcode) {
	case TCODE_WRITE_BLOCK_REQUEST:
		spin_lock_bh(&agent->lock);
		if (agent->state != AGENT_STATE_SUSPENDED &&
				agent->state != AGENT_STATE_RESET) {
			spin_unlock_bh(&agent->lock);
			pr_notice("Ignoring ORB_POINTER write while active.\n");
			return RCODE_CONFLICT_ERROR;
		}
		agent->state = AGENT_STATE_ACTIVE;
		spin_unlock_bh(&agent->lock);

		agent->orb_pointer = sbp2_pointer_to_addr(ptr);
		agent->doorbell = false;

		pr_debug("tgt_agent ORB_POINTER write: 0x%llx\n",
				agent->orb_pointer);

		queue_work(system_unbound_wq, &agent->work);

		return RCODE_COMPLETE;

	case TCODE_READ_BLOCK_REQUEST:
		pr_debug("tgt_agent ORB_POINTER READ\n");
		spin_lock_bh(&agent->lock);
		addr_to_sbp2_pointer(agent->orb_pointer, ptr);
		spin_unlock_bh(&agent->lock);
		return RCODE_COMPLETE;

	default:
		return RCODE_TYPE_ERROR;
	}
}