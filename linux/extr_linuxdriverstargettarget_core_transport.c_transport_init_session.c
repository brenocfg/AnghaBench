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
struct se_session {int /*<<< orphan*/  cmd_count; int /*<<< orphan*/  cmd_list_wq; int /*<<< orphan*/  sess_cmd_lock; int /*<<< orphan*/  sess_cmd_list; int /*<<< orphan*/  sess_acl_list; int /*<<< orphan*/  sess_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int percpu_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_release_sess_cmd_refcnt ; 

int transport_init_session(struct se_session *se_sess)
{
	INIT_LIST_HEAD(&se_sess->sess_list);
	INIT_LIST_HEAD(&se_sess->sess_acl_list);
	INIT_LIST_HEAD(&se_sess->sess_cmd_list);
	spin_lock_init(&se_sess->sess_cmd_lock);
	init_waitqueue_head(&se_sess->cmd_list_wq);
	return percpu_ref_init(&se_sess->cmd_count,
			       target_release_sess_cmd_refcnt, 0, GFP_KERNEL);
}