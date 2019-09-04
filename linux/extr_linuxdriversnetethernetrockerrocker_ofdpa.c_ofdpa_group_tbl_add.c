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
struct ofdpa_port {int /*<<< orphan*/  rocker_port; struct ofdpa* ofdpa; } ;
struct ofdpa_group_tbl_entry {int /*<<< orphan*/  group_id; int /*<<< orphan*/  entry; int /*<<< orphan*/  cmd; } ;
struct ofdpa {int /*<<< orphan*/  group_tbl_lock; int /*<<< orphan*/  group_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKER_TLV_CMD_TYPE_OF_DPA_GROUP_ADD ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_TYPE_OF_DPA_GROUP_MOD ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofdpa_cmd_group_tbl_add ; 
 int /*<<< orphan*/  ofdpa_flags_nowait (int) ; 
 int /*<<< orphan*/  ofdpa_group_tbl_entry_free (struct ofdpa_group_tbl_entry*) ; 
 struct ofdpa_group_tbl_entry* ofdpa_group_tbl_find (struct ofdpa*,struct ofdpa_group_tbl_entry*) ; 
 int rocker_cmd_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ofdpa_group_tbl_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ofdpa_group_tbl_add(struct ofdpa_port *ofdpa_port, int flags,
			       struct ofdpa_group_tbl_entry *match)
{
	struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	struct ofdpa_group_tbl_entry *found;
	unsigned long lock_flags;

	spin_lock_irqsave(&ofdpa->group_tbl_lock, lock_flags);

	found = ofdpa_group_tbl_find(ofdpa, match);

	if (found) {
		hash_del(&found->entry);
		ofdpa_group_tbl_entry_free(found);
		found = match;
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_GROUP_MOD;
	} else {
		found = match;
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_GROUP_ADD;
	}

	hash_add(ofdpa->group_tbl, &found->entry, found->group_id);

	spin_unlock_irqrestore(&ofdpa->group_tbl_lock, lock_flags);

	return rocker_cmd_exec(ofdpa_port->rocker_port,
			       ofdpa_flags_nowait(flags),
			       ofdpa_cmd_group_tbl_add,
			       found, NULL, NULL);
}