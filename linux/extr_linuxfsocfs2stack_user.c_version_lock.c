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
struct ocfs2_live_connection {int /*<<< orphan*/  oc_version_lksb; } ;
struct ocfs2_cluster_connection {struct ocfs2_live_connection* cc_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERSION_LOCK ; 
 int sync_lock (struct ocfs2_cluster_connection*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int version_lock(struct ocfs2_cluster_connection *conn, int mode,
		int flags)
{
	struct ocfs2_live_connection *lc = conn->cc_private;
	return sync_lock(conn, mode, flags,
			&lc->oc_version_lksb, VERSION_LOCK);
}