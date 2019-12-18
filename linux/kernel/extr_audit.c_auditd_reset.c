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
struct sk_buff {int dummy; } ;
typedef  struct auditd_connection {int /*<<< orphan*/  rcu; } const auditd_connection ;

/* Variables and functions */
 int /*<<< orphan*/  audit_retry_queue ; 
 int /*<<< orphan*/  auditd_conn ; 
 int /*<<< orphan*/  auditd_conn_free ; 
 int /*<<< orphan*/  auditd_conn_lock ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauditd_hold_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct auditd_connection const* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void auditd_reset(const struct auditd_connection *ac)
{
	unsigned long flags;
	struct sk_buff *skb;
	struct auditd_connection *ac_old;

	/* if it isn't already broken, break the connection */
	spin_lock_irqsave(&auditd_conn_lock, flags);
	ac_old = rcu_dereference_protected(auditd_conn,
					   lockdep_is_held(&auditd_conn_lock));
	if (ac && ac != ac_old) {
		/* someone already registered a new auditd connection */
		spin_unlock_irqrestore(&auditd_conn_lock, flags);
		return;
	}
	rcu_assign_pointer(auditd_conn, NULL);
	spin_unlock_irqrestore(&auditd_conn_lock, flags);

	if (ac_old)
		call_rcu(&ac_old->rcu, auditd_conn_free);

	/* flush the retry queue to the hold queue, but don't touch the main
	 * queue since we need to process that normally for multicast */
	while ((skb = skb_dequeue(&audit_retry_queue)))
		kauditd_hold_skb(skb);
}