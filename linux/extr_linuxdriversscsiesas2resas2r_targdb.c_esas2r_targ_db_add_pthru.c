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
typedef  int u8 ;
struct esas2r_target {scalar_t__ target_state; int virt_targ_id; int identifier_len; int flags; int /*<<< orphan*/  identifier; int /*<<< orphan*/  phys_targ_id; scalar_t__ inter_block; scalar_t__ inter_byte; scalar_t__ block_size; } ;
struct esas2r_disc_context {scalar_t__ curr_virt_id; int /*<<< orphan*/  curr_phys_id; } ;
struct esas2r_adapter {struct esas2r_target* targetdb; } ;

/* Variables and functions */
 scalar_t__ ESAS2R_MAX_TARGETS ; 
 int TF_PASS_THRU ; 
 int TF_USED ; 
 scalar_t__ TS_PRESENT ; 
 int /*<<< orphan*/  esas2r_bugon () ; 
 int /*<<< orphan*/  esas2r_hdebug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct esas2r_target* esas2r_targ_db_find_by_ident (struct esas2r_adapter*,int*,int) ; 
 int /*<<< orphan*/  esas2r_targ_get_id (struct esas2r_target*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

struct esas2r_target *esas2r_targ_db_add_pthru(struct esas2r_adapter *a,
					       struct esas2r_disc_context *dc,
					       u8 *ident,
					       u8 ident_len)
{
	struct esas2r_target *t;

	esas2r_trace_enter();

	if (dc->curr_virt_id >= ESAS2R_MAX_TARGETS) {
		esas2r_bugon();
		esas2r_trace_exit();
		return NULL;
	}

	/* see if we found this device before. */

	t = esas2r_targ_db_find_by_ident(a, ident, ident_len);

	if (t == NULL) {
		t = a->targetdb + dc->curr_virt_id;

		if (ident_len > sizeof(t->identifier)
		    || t->target_state == TS_PRESENT) {
			esas2r_trace_exit();
			return NULL;
		}
	}

	esas2r_hdebug("add PT; T:%d, V:%d, P:%d", esas2r_targ_get_id(t, a),
		      dc->curr_virt_id,
		      dc->curr_phys_id);

	t->block_size = 0;
	t->inter_byte = 0;
	t->inter_block = 0;
	t->virt_targ_id = dc->curr_virt_id;
	t->phys_targ_id = dc->curr_phys_id;
	t->identifier_len = ident_len;

	memcpy(t->identifier, ident, ident_len);

	t->flags |= TF_PASS_THRU | TF_USED;

	t->target_state = TS_PRESENT;

	return t;
}