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
struct pid {int dummy; } ;
struct net {int dummy; } ;
struct auditd_connection {int /*<<< orphan*/  rcu; int /*<<< orphan*/  net; int /*<<< orphan*/  portid; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  auditd_conn ; 
 int /*<<< orphan*/  auditd_conn_free ; 
 int /*<<< orphan*/  auditd_conn_lock ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_net (struct net*) ; 
 int /*<<< orphan*/  get_pid (struct pid*) ; 
 struct auditd_connection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct auditd_connection*) ; 
 struct auditd_connection* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int auditd_set(struct pid *pid, u32 portid, struct net *net)
{
	unsigned long flags;
	struct auditd_connection *ac_old, *ac_new;

	if (!pid || !net)
		return -EINVAL;

	ac_new = kzalloc(sizeof(*ac_new), GFP_KERNEL);
	if (!ac_new)
		return -ENOMEM;
	ac_new->pid = get_pid(pid);
	ac_new->portid = portid;
	ac_new->net = get_net(net);

	spin_lock_irqsave(&auditd_conn_lock, flags);
	ac_old = rcu_dereference_protected(auditd_conn,
					   lockdep_is_held(&auditd_conn_lock));
	rcu_assign_pointer(auditd_conn, ac_new);
	spin_unlock_irqrestore(&auditd_conn_lock, flags);

	if (ac_old)
		call_rcu(&ac_old->rcu, auditd_conn_free);

	return 0;
}