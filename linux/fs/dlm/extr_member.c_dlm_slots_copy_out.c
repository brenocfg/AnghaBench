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
struct rcom_slot {int /*<<< orphan*/  ro_slot; int /*<<< orphan*/  ro_nodeid; } ;
struct rcom_config {int dummy; } ;
struct dlm_slot {int /*<<< orphan*/  slot; int /*<<< orphan*/  nodeid; } ;
struct dlm_rcom {scalar_t__ rc_buf; } ;
struct dlm_ls {int ls_slots_size; struct dlm_slot* ls_slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

void dlm_slots_copy_out(struct dlm_ls *ls, struct dlm_rcom *rc)
{
	struct dlm_slot *slot;
	struct rcom_slot *ro;
	int i;

	ro = (struct rcom_slot *)(rc->rc_buf + sizeof(struct rcom_config));

	/* ls_slots array is sparse, but not rcom_slots */

	for (i = 0; i < ls->ls_slots_size; i++) {
		slot = &ls->ls_slots[i];
		if (!slot->nodeid)
			continue;
		ro->ro_nodeid = cpu_to_le32(slot->nodeid);
		ro->ro_slot = cpu_to_le16(slot->slot);
		ro++;
	}
}