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
typedef  int time64_t ;
struct afs_volume {int /*<<< orphan*/  cb_v_break; } ;
struct afs_vnode {unsigned int cb_break; unsigned int cb_s_break; unsigned int cb_v_break; int cb_expires_at; int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  fid; int /*<<< orphan*/  flags; int /*<<< orphan*/  cb_interest; struct afs_volume* volume; } ;
struct afs_server {int /*<<< orphan*/  cb_s_break; } ;
struct afs_cb_interest {int /*<<< orphan*/  server; } ;
typedef  enum afs_cb_break_reason { ____Placeholder_afs_cb_break_reason } afs_cb_break_reason ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_CB_PROMISED ; 
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int /*<<< orphan*/  AFS_VNODE_ZAP_DATA ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __afs_break_callback (struct afs_vnode*,int) ; 
 int afs_cb_break_for_lapsed ; 
 int afs_cb_break_for_vsbreak ; 
 int afs_cb_break_for_zap ; 
 int afs_cb_break_no_break ; 
 int /*<<< orphan*/  done_seqretry (int /*<<< orphan*/ *,int) ; 
 int ktime_get_real_seconds () ; 
 scalar_t__ need_seqretry (int /*<<< orphan*/ *,int) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_seqbegin_or_lock (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_cb_miss (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

bool afs_check_validity(struct afs_vnode *vnode)
{
	struct afs_cb_interest *cbi;
	struct afs_server *server;
	struct afs_volume *volume = vnode->volume;
	enum afs_cb_break_reason need_clear = afs_cb_break_no_break;
	time64_t now = ktime_get_real_seconds();
	bool valid;
	unsigned int cb_break, cb_s_break, cb_v_break;
	int seq = 0;

	do {
		read_seqbegin_or_lock(&vnode->cb_lock, &seq);
		cb_v_break = READ_ONCE(volume->cb_v_break);
		cb_break = vnode->cb_break;

		if (test_bit(AFS_VNODE_CB_PROMISED, &vnode->flags)) {
			cbi = rcu_dereference(vnode->cb_interest);
			server = rcu_dereference(cbi->server);
			cb_s_break = READ_ONCE(server->cb_s_break);

			if (vnode->cb_s_break != cb_s_break ||
			    vnode->cb_v_break != cb_v_break) {
				vnode->cb_s_break = cb_s_break;
				vnode->cb_v_break = cb_v_break;
				need_clear = afs_cb_break_for_vsbreak;
				valid = false;
			} else if (test_bit(AFS_VNODE_ZAP_DATA, &vnode->flags)) {
				need_clear = afs_cb_break_for_zap;
				valid = false;
			} else if (vnode->cb_expires_at - 10 <= now) {
				need_clear = afs_cb_break_for_lapsed;
				valid = false;
			} else {
				valid = true;
			}
		} else if (test_bit(AFS_VNODE_DELETED, &vnode->flags)) {
			valid = true;
		} else {
			vnode->cb_v_break = cb_v_break;
			valid = false;
		}

	} while (need_seqretry(&vnode->cb_lock, seq));

	done_seqretry(&vnode->cb_lock, seq);

	if (need_clear != afs_cb_break_no_break) {
		write_seqlock(&vnode->cb_lock);
		if (cb_break == vnode->cb_break)
			__afs_break_callback(vnode, need_clear);
		else
			trace_afs_cb_miss(&vnode->fid, need_clear);
		write_sequnlock(&vnode->cb_lock);
		valid = false;
	}

	return valid;
}