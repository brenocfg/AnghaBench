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
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct ocfs2_cluster_connection {int dummy; } ;

/* Variables and functions */
 struct ocfs2_cluster_connection* ERR_PTR (int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_cluster_connect_agnostic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_cluster_connection**) ; 
 int /*<<< orphan*/  user_dlm_lproto ; 
 int /*<<< orphan*/  user_dlm_recovery_handler_noop ; 

struct ocfs2_cluster_connection *user_dlm_register(const struct qstr *name)
{
	int rc;
	struct ocfs2_cluster_connection *conn;

	rc = ocfs2_cluster_connect_agnostic(name->name, name->len,
					    &user_dlm_lproto,
					    user_dlm_recovery_handler_noop,
					    NULL, &conn);
	if (rc)
		mlog_errno(rc);

	return rc ? ERR_PTR(rc) : conn;
}