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
struct ocfs2_cluster_connection {int /*<<< orphan*/ * cc_private; int /*<<< orphan*/ * cc_lockspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_release_lockspace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocfs2_live_connection_drop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  version_unlock (struct ocfs2_cluster_connection*) ; 

__attribute__((used)) static int user_cluster_disconnect(struct ocfs2_cluster_connection *conn)
{
	version_unlock(conn);
	dlm_release_lockspace(conn->cc_lockspace, 2);
	conn->cc_lockspace = NULL;
	ocfs2_live_connection_drop(conn->cc_private);
	conn->cc_private = NULL;
	return 0;
}