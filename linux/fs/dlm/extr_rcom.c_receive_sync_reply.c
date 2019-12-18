#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_nodeid; } ;
struct dlm_rcom {scalar_t__ rc_id; TYPE_1__ rc_header; int /*<<< orphan*/  rc_type; } ;
struct dlm_ls {scalar_t__ ls_rcom_seq; int /*<<< orphan*/  ls_rcom_spin; int /*<<< orphan*/  ls_wait_general; int /*<<< orphan*/  ls_flags; int /*<<< orphan*/  ls_recover_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSFL_RCOM_READY ; 
 int /*<<< orphan*/  LSFL_RCOM_WAIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct dlm_rcom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void receive_sync_reply(struct dlm_ls *ls, struct dlm_rcom *rc_in)
{
	spin_lock(&ls->ls_rcom_spin);
	if (!test_bit(LSFL_RCOM_WAIT, &ls->ls_flags) ||
	    rc_in->rc_id != ls->ls_rcom_seq) {
		log_debug(ls, "reject reply %d from %d seq %llx expect %llx",
			  rc_in->rc_type, rc_in->rc_header.h_nodeid,
			  (unsigned long long)rc_in->rc_id,
			  (unsigned long long)ls->ls_rcom_seq);
		goto out;
	}
	memcpy(ls->ls_recover_buf, rc_in, rc_in->rc_header.h_length);
	set_bit(LSFL_RCOM_READY, &ls->ls_flags);
	clear_bit(LSFL_RCOM_WAIT, &ls->ls_flags);
	wake_up(&ls->ls_wait_general);
 out:
	spin_unlock(&ls->ls_rcom_spin);
}