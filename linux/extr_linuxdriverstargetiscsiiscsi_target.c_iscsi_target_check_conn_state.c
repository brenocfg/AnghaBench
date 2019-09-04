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
struct iscsi_conn {scalar_t__ conn_state; int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 scalar_t__ TARG_CONN_STATE_LOGGED_IN ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool iscsi_target_check_conn_state(struct iscsi_conn *conn)
{
	bool ret;

	spin_lock_bh(&conn->state_lock);
	ret = (conn->conn_state != TARG_CONN_STATE_LOGGED_IN);
	spin_unlock_bh(&conn->state_lock);

	return ret;
}