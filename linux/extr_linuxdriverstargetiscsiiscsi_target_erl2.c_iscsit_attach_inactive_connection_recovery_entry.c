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
struct iscsi_session {int /*<<< orphan*/  cr_i_lock; int /*<<< orphan*/  sid; int /*<<< orphan*/  conn_recovery_count; int /*<<< orphan*/  cr_inactive_list; } ;
struct iscsi_conn_recovery {int /*<<< orphan*/  cr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsit_attach_inactive_connection_recovery_entry(
	struct iscsi_session *sess,
	struct iscsi_conn_recovery *cr)
{
	spin_lock(&sess->cr_i_lock);
	list_add_tail(&cr->cr_list, &sess->cr_inactive_list);

	sess->conn_recovery_count++;
	pr_debug("Incremented connection recovery count to %u for"
		" SID: %u\n", sess->conn_recovery_count, sess->sid);
	spin_unlock(&sess->cr_i_lock);

	return 0;
}