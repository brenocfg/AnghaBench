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
struct sbp_target_agent {int state; int /*<<< orphan*/  lock; } ;
struct fw_card {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int RCODE_COMPLETE ; 
 int RCODE_TYPE_ERROR ; 
#define  TCODE_READ_QUADLET_REQUEST 129 
#define  TCODE_WRITE_QUADLET_REQUEST 128 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tgt_agent_rw_agent_state(struct fw_card *card, int tcode, void *data,
		struct sbp_target_agent *agent)
{
	int state;

	switch (tcode) {
	case TCODE_READ_QUADLET_REQUEST:
		pr_debug("tgt_agent AGENT_STATE READ\n");

		spin_lock_bh(&agent->lock);
		state = agent->state;
		spin_unlock_bh(&agent->lock);

		*(__be32 *)data = cpu_to_be32(state);

		return RCODE_COMPLETE;

	case TCODE_WRITE_QUADLET_REQUEST:
		/* ignored */
		return RCODE_COMPLETE;

	default:
		return RCODE_TYPE_ERROR;
	}
}