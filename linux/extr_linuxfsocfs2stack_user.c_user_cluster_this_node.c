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
struct ocfs2_live_connection {scalar_t__ oc_type; int /*<<< orphan*/  oc_this_node; } ;
struct ocfs2_cluster_connection {struct ocfs2_live_connection* cc_private; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NO_CONTROLD ; 
 scalar_t__ WITH_CONTROLD ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int ocfs2_control_get_this_node () ; 

__attribute__((used)) static int user_cluster_this_node(struct ocfs2_cluster_connection *conn,
				  unsigned int *this_node)
{
	int rc;
	struct ocfs2_live_connection *lc = conn->cc_private;

	if (lc->oc_type == WITH_CONTROLD)
		rc = ocfs2_control_get_this_node();
	else if (lc->oc_type == NO_CONTROLD)
		rc = atomic_read(&lc->oc_this_node);
	else
		rc = -EINVAL;

	if (rc < 0)
		return rc;

	*this_node = rc;
	return 0;
}