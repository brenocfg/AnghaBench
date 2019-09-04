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
struct ofdpa_group_tbl_entry {int /*<<< orphan*/  cmd; int /*<<< orphan*/  entry; } ;
struct ofdpa {int /*<<< orphan*/  group_tbl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKER_TLV_CMD_TYPE_OF_DPA_GROUP_DEL ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofdpa_cmd_group_tbl_del ; 
 int /*<<< orphan*/  ofdpa_flags_nowait (int) ; 
 int /*<<< orphan*/  ofdpa_group_tbl_entry_free (struct ofdpa_group_tbl_entry*) ; 
 struct ofdpa_group_tbl_entry* ofdpa_group_tbl_find (struct ofdpa*,struct ofdpa_group_tbl_entry*) ; 
 int rocker_cmd_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ofdpa_group_tbl_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ofdpa_group_tbl_del(struct ofdpa_port *ofdpa_port, int flags,
			       struct ofdpa_group_tbl_entry *match)
{
	struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	struct ofdpa_group_tbl_entry *found;
	unsigned long lock_flags;
	int err = 0;

	spin_lock_irqsave(&ofdpa->group_tbl_lock, lock_flags);

	found = ofdpa_group_tbl_find(ofdpa, match);

	if (found) {
		hash_del(&found->entry);
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_GROUP_DEL;
	}

	spin_unlock_irqrestore(&ofdpa->group_tbl_lock, lock_flags);

	ofdpa_group_tbl_entry_free(match);

	if (found) {
		err = rocker_cmd_exec(ofdpa_port->rocker_port,
				      ofdpa_flags_nowait(flags),
				      ofdpa_cmd_group_tbl_del,
				      found, NULL, NULL);
		ofdpa_group_tbl_entry_free(found);
	}

	return err;
}