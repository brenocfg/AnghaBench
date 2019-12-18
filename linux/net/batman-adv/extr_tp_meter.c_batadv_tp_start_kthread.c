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
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int dummy; } ;
struct batadv_tp_vars {int /*<<< orphan*/  other_end; int /*<<< orphan*/  icmp_uid; int /*<<< orphan*/  session; int /*<<< orphan*/  refcount; struct batadv_priv* bat_priv; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_TP_REASON_MEMORY_ERROR ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  batadv_tp_batctl_error_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tp_send ; 
 int /*<<< orphan*/  batadv_tp_sender_cleanup (struct batadv_priv*,struct batadv_tp_vars*) ; 
 int /*<<< orphan*/  batadv_tp_session_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tp_vars_put (struct batadv_tp_vars*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct task_struct* kthread_create (int /*<<< orphan*/ ,struct batadv_tp_vars*,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static void batadv_tp_start_kthread(struct batadv_tp_vars *tp_vars)
{
	struct task_struct *kthread;
	struct batadv_priv *bat_priv = tp_vars->bat_priv;
	u32 session_cookie;

	kref_get(&tp_vars->refcount);
	kthread = kthread_create(batadv_tp_send, tp_vars, "kbatadv_tp_meter");
	if (IS_ERR(kthread)) {
		session_cookie = batadv_tp_session_cookie(tp_vars->session,
							  tp_vars->icmp_uid);
		pr_err("batadv: cannot create tp meter kthread\n");
		batadv_tp_batctl_error_notify(BATADV_TP_REASON_MEMORY_ERROR,
					      tp_vars->other_end,
					      bat_priv, session_cookie);

		/* drop reserved reference for kthread */
		batadv_tp_vars_put(tp_vars);

		/* cleanup of failed tp meter variables */
		batadv_tp_sender_cleanup(bat_priv, tp_vars);
		return;
	}

	wake_up_process(kthread);
}