#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_protocol_version {scalar_t__ pv_major; scalar_t__ pv_minor; } ;
struct TYPE_8__ {int /*<<< orphan*/  sb_lvbptr; } ;
struct ocfs2_live_connection {int /*<<< orphan*/  oc_lvb; TYPE_2__ oc_version_lksb; } ;
struct TYPE_9__ {scalar_t__ pv_major; scalar_t__ pv_minor; } ;
struct ocfs2_cluster_connection {TYPE_3__ cc_version; struct ocfs2_live_connection* cc_private; } ;
struct TYPE_7__ {scalar_t__ pv_major; scalar_t__ pv_minor; } ;
struct TYPE_11__ {TYPE_1__ sp_max_proto; } ;
struct TYPE_10__ {scalar_t__ pv_major; scalar_t__ pv_minor; } ;

/* Variables and functions */
 int DLM_LKF_CONVERT ; 
 int DLM_LKF_NOQUEUE ; 
 int DLM_LKF_VALBLK ; 
 int /*<<< orphan*/  DLM_LOCK_EX ; 
 int /*<<< orphan*/  DLM_LOCK_PR ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  lvb_to_version (int /*<<< orphan*/ ,struct ocfs2_protocol_version*) ; 
 TYPE_6__ ocfs2_user_plugin ; 
 TYPE_4__ running_proto ; 
 int version_lock (struct ocfs2_cluster_connection*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  version_to_lvb (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_protocol_version(struct ocfs2_cluster_connection *conn)
{
	int ret;
	struct ocfs2_live_connection *lc = conn->cc_private;
	struct ocfs2_protocol_version pv;

	running_proto.pv_major =
		ocfs2_user_plugin.sp_max_proto.pv_major;
	running_proto.pv_minor =
		ocfs2_user_plugin.sp_max_proto.pv_minor;

	lc->oc_version_lksb.sb_lvbptr = lc->oc_lvb;
	ret = version_lock(conn, DLM_LOCK_EX,
			DLM_LKF_VALBLK|DLM_LKF_NOQUEUE);
	if (!ret) {
		conn->cc_version.pv_major = running_proto.pv_major;
		conn->cc_version.pv_minor = running_proto.pv_minor;
		version_to_lvb(&running_proto, lc->oc_lvb);
		version_lock(conn, DLM_LOCK_PR, DLM_LKF_CONVERT|DLM_LKF_VALBLK);
	} else if (ret == -EAGAIN) {
		ret = version_lock(conn, DLM_LOCK_PR, DLM_LKF_VALBLK);
		if (ret)
			goto out;
		lvb_to_version(lc->oc_lvb, &pv);

		if ((pv.pv_major != running_proto.pv_major) ||
				(pv.pv_minor > running_proto.pv_minor)) {
			ret = -EINVAL;
			goto out;
		}

		conn->cc_version.pv_major = pv.pv_major;
		conn->cc_version.pv_minor = pv.pv_minor;
	}
out:
	return ret;
}