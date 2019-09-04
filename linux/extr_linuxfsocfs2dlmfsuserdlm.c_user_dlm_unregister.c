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
struct ocfs2_cluster_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_cluster_disconnect (struct ocfs2_cluster_connection*,int /*<<< orphan*/ ) ; 

void user_dlm_unregister(struct ocfs2_cluster_connection *conn)
{
	ocfs2_cluster_disconnect(conn, 0);
}