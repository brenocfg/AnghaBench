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
struct ofdpa_flow_tbl_entry {size_t key_len; int /*<<< orphan*/  key_crc32; int /*<<< orphan*/  entry; int /*<<< orphan*/  cmd; scalar_t__ cookie; int /*<<< orphan*/  key; } ;
struct ofdpa {int /*<<< orphan*/  flow_tbl_lock; int /*<<< orphan*/  flow_tbl; int /*<<< orphan*/  flow_tbl_next_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKER_TLV_CMD_TYPE_OF_DPA_FLOW_ADD ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_TYPE_OF_DPA_FLOW_MOD ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ofdpa_flow_tbl_entry*) ; 
 int /*<<< orphan*/  ofdpa_cmd_flow_tbl_add ; 
 int /*<<< orphan*/  ofdpa_flags_nowait (int) ; 
 struct ofdpa_flow_tbl_entry* ofdpa_flow_tbl_find (struct ofdpa*,struct ofdpa_flow_tbl_entry*) ; 
 int rocker_cmd_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ofdpa_flow_tbl_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ofdpa_flow_tbl_add(struct ofdpa_port *ofdpa_port,
			      int flags, struct ofdpa_flow_tbl_entry *match)
{
	struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	struct ofdpa_flow_tbl_entry *found;
	size_t key_len = match->key_len ? match->key_len : sizeof(found->key);
	unsigned long lock_flags;

	match->key_crc32 = crc32(~0, &match->key, key_len);

	spin_lock_irqsave(&ofdpa->flow_tbl_lock, lock_flags);

	found = ofdpa_flow_tbl_find(ofdpa, match);

	if (found) {
		match->cookie = found->cookie;
		hash_del(&found->entry);
		kfree(found);
		found = match;
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_FLOW_MOD;
	} else {
		found = match;
		found->cookie = ofdpa->flow_tbl_next_cookie++;
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_FLOW_ADD;
	}

	hash_add(ofdpa->flow_tbl, &found->entry, found->key_crc32);
	spin_unlock_irqrestore(&ofdpa->flow_tbl_lock, lock_flags);

	return rocker_cmd_exec(ofdpa_port->rocker_port,
			       ofdpa_flags_nowait(flags),
			       ofdpa_cmd_flow_tbl_add,
			       found, NULL, NULL);
}