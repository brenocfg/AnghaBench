#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pv_major; scalar_t__ pv_minor; } ;
struct ocfs2_control_private {scalar_t__ op_state; scalar_t__ op_this_node; TYPE_1__ op_proto; } ;
struct file {struct ocfs2_control_private* private_data; } ;
struct TYPE_4__ {scalar_t__ pv_major; scalar_t__ pv_minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 scalar_t__ OCFS2_CONTROL_HANDSHAKE_PROTOCOL ; 
 int /*<<< orphan*/  OCFS2_CONTROL_HANDSHAKE_VALID ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_control_lock ; 
 int /*<<< orphan*/  ocfs2_control_opened ; 
 int /*<<< orphan*/  ocfs2_control_set_handshake_state (struct file*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_control_this_node ; 
 int /*<<< orphan*/  ocfs2_live_connection_list ; 
 TYPE_2__ running_proto ; 

__attribute__((used)) static int ocfs2_control_install_private(struct file *file)
{
	int rc = 0;
	int set_p = 1;
	struct ocfs2_control_private *p = file->private_data;

	BUG_ON(p->op_state != OCFS2_CONTROL_HANDSHAKE_PROTOCOL);

	mutex_lock(&ocfs2_control_lock);

	if (p->op_this_node < 0) {
		set_p = 0;
	} else if ((ocfs2_control_this_node >= 0) &&
		   (ocfs2_control_this_node != p->op_this_node)) {
		rc = -EINVAL;
		goto out_unlock;
	}

	if (!p->op_proto.pv_major) {
		set_p = 0;
	} else if (!list_empty(&ocfs2_live_connection_list) &&
		   ((running_proto.pv_major != p->op_proto.pv_major) ||
		    (running_proto.pv_minor != p->op_proto.pv_minor))) {
		rc = -EINVAL;
		goto out_unlock;
	}

	if (set_p) {
		ocfs2_control_this_node = p->op_this_node;
		running_proto.pv_major = p->op_proto.pv_major;
		running_proto.pv_minor = p->op_proto.pv_minor;
	}

out_unlock:
	mutex_unlock(&ocfs2_control_lock);

	if (!rc && set_p) {
		/* We set the global values successfully */
		atomic_inc(&ocfs2_control_opened);
		ocfs2_control_set_handshake_state(file,
					OCFS2_CONTROL_HANDSHAKE_VALID);
	}

	return rc;
}