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
struct esas2r_target {scalar_t__ target_state; int block_size; int inter_byte; int inter_block; int virt_targ_id; scalar_t__ identifier_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  phys_targ_id; } ;
struct esas2r_disc_context {scalar_t__ curr_virt_id; int interleave; int block_size; int /*<<< orphan*/  raid_grp_name; } ;
struct esas2r_adapter {struct esas2r_target* targetdb; } ;

/* Variables and functions */
 scalar_t__ ESAS2R_MAX_TARGETS ; 
 int /*<<< orphan*/  ESAS2R_TARG_ID_INV ; 
 int /*<<< orphan*/  TF_PASS_THRU ; 
 int /*<<< orphan*/  TF_USED ; 
 scalar_t__ TS_PRESENT ; 
 int /*<<< orphan*/  esas2r_bugon () ; 
 int /*<<< orphan*/  esas2r_hdebug (char*,...) ; 
 int /*<<< orphan*/  esas2r_targ_get_id (struct esas2r_target*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 

struct esas2r_target *esas2r_targ_db_add_raid(struct esas2r_adapter *a,
					      struct esas2r_disc_context *
					      dc)
{
	struct esas2r_target *t;

	esas2r_trace_enter();

	if (dc->curr_virt_id >= ESAS2R_MAX_TARGETS) {
		esas2r_bugon();
		esas2r_trace_exit();
		return NULL;
	}

	t = a->targetdb + dc->curr_virt_id;

	if (t->target_state == TS_PRESENT) {
		esas2r_trace_exit();
		return NULL;
	}

	esas2r_hdebug("add RAID %s, T:%d", dc->raid_grp_name,
		      esas2r_targ_get_id(
			      t,
			      a));

	if (dc->interleave == 0
	    || dc->block_size  == 0) {
		/* these are invalid values, don't create the target entry. */

		esas2r_hdebug("invalid RAID group dimensions");

		esas2r_trace_exit();

		return NULL;
	}

	t->block_size = dc->block_size;
	t->inter_byte = dc->interleave;
	t->inter_block = dc->interleave / dc->block_size;
	t->virt_targ_id = dc->curr_virt_id;
	t->phys_targ_id = ESAS2R_TARG_ID_INV;

	t->flags &= ~TF_PASS_THRU;
	t->flags |= TF_USED;

	t->identifier_len = 0;

	t->target_state = TS_PRESENT;

	return t;
}