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
struct iscsi_session {int /*<<< orphan*/  cr_i_lock; } ;
struct iscsi_conn_recovery {int /*<<< orphan*/  cr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsit_remove_inactive_connection_recovery_entry(
	struct iscsi_conn_recovery *cr,
	struct iscsi_session *sess)
{
	spin_lock(&sess->cr_i_lock);
	list_del(&cr->cr_list);
	spin_unlock(&sess->cr_i_lock);
}