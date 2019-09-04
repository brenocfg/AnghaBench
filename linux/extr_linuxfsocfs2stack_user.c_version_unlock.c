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
 int sync_unlock (struct ocfs2_cluster_connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int version_unlock(struct ocfs2_cluster_connection *conn)
{
	struct ocfs2_live_connection *lc = conn->cc_private;
	return sync_unlock(conn, &lc->oc_version_lksb, VERSION_LOCK);
}