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
struct iscsi_session {int /*<<< orphan*/  session_usage_lock; int /*<<< orphan*/  session_waiting_on_uc_comp; scalar_t__ session_waiting_on_uc; int /*<<< orphan*/  session_usage_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsit_dec_session_usage_count(struct iscsi_session *sess)
{
	spin_lock_bh(&sess->session_usage_lock);
	sess->session_usage_count--;

	if (!sess->session_usage_count && sess->session_waiting_on_uc)
		complete(&sess->session_waiting_on_uc_comp);

	spin_unlock_bh(&sess->session_usage_lock);
}