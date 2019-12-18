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
struct sock {int dummy; } ;
struct net {int dummy; } ;
struct auditd_connection {int /*<<< orphan*/  portid; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int UNICAST_RETRIES ; 
 int /*<<< orphan*/  audit_backlog_wait ; 
 struct sock* audit_get_sk (struct net*) ; 
 int /*<<< orphan*/  audit_hold_queue ; 
 int /*<<< orphan*/  audit_queue ; 
 int /*<<< orphan*/  audit_retry_queue ; 
 int /*<<< orphan*/  auditd_conn ; 
 int /*<<< orphan*/  auditd_reset (struct auditd_connection*) ; 
 struct net* get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauditd_hold_skb ; 
 int /*<<< orphan*/  kauditd_rehold_skb ; 
 int /*<<< orphan*/  kauditd_retry_skb ; 
 int /*<<< orphan*/ * kauditd_send_multicast_skb ; 
 int kauditd_send_queue (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauditd_wait ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 struct auditd_connection* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_freezable () ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_freezable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kauditd_thread(void *dummy)
{
	int rc;
	u32 portid = 0;
	struct net *net = NULL;
	struct sock *sk = NULL;
	struct auditd_connection *ac;

#define UNICAST_RETRIES 5

	set_freezable();
	while (!kthread_should_stop()) {
		/* NOTE: see the lock comments in auditd_send_unicast_skb() */
		rcu_read_lock();
		ac = rcu_dereference(auditd_conn);
		if (!ac) {
			rcu_read_unlock();
			goto main_queue;
		}
		net = get_net(ac->net);
		sk = audit_get_sk(net);
		portid = ac->portid;
		rcu_read_unlock();

		/* attempt to flush the hold queue */
		rc = kauditd_send_queue(sk, portid,
					&audit_hold_queue, UNICAST_RETRIES,
					NULL, kauditd_rehold_skb);
		if (ac && rc < 0) {
			sk = NULL;
			auditd_reset(ac);
			goto main_queue;
		}

		/* attempt to flush the retry queue */
		rc = kauditd_send_queue(sk, portid,
					&audit_retry_queue, UNICAST_RETRIES,
					NULL, kauditd_hold_skb);
		if (ac && rc < 0) {
			sk = NULL;
			auditd_reset(ac);
			goto main_queue;
		}

main_queue:
		/* process the main queue - do the multicast send and attempt
		 * unicast, dump failed record sends to the retry queue; if
		 * sk == NULL due to previous failures we will just do the
		 * multicast send and move the record to the hold queue */
		rc = kauditd_send_queue(sk, portid, &audit_queue, 1,
					kauditd_send_multicast_skb,
					(sk ?
					 kauditd_retry_skb : kauditd_hold_skb));
		if (ac && rc < 0)
			auditd_reset(ac);
		sk = NULL;

		/* drop our netns reference, no auditd sends past this line */
		if (net) {
			put_net(net);
			net = NULL;
		}

		/* we have processed all the queues so wake everyone */
		wake_up(&audit_backlog_wait);

		/* NOTE: we want to wake up if there is anything on the queue,
		 *       regardless of if an auditd is connected, as we need to
		 *       do the multicast send and rotate records from the
		 *       main queue to the retry/hold queues */
		wait_event_freezable(kauditd_wait,
				     (skb_queue_len(&audit_queue) ? 1 : 0));
	}

	return 0;
}