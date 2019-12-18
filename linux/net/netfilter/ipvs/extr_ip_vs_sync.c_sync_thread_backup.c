#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sync_maxlen; int /*<<< orphan*/  syncid; int /*<<< orphan*/  mcast_ifn; } ;
struct netns_ipvs {TYPE_1__ bcfg; } ;
struct ip_vs_sync_thread_data {int /*<<< orphan*/  buf; TYPE_3__* sock; int /*<<< orphan*/  id; struct netns_ipvs* ipvs; } ;
struct TYPE_6__ {TYPE_2__* sk; } ;
struct TYPE_5__ {int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ip_vs_process_message (struct netns_ipvs*,int /*<<< orphan*/ ,int) ; 
 int ip_vs_receive (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_sleep (TYPE_2__*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sync_thread_backup(void *data)
{
	struct ip_vs_sync_thread_data *tinfo = data;
	struct netns_ipvs *ipvs = tinfo->ipvs;
	int len;

	pr_info("sync thread started: state = BACKUP, mcast_ifn = %s, "
		"syncid = %d, id = %d\n",
		ipvs->bcfg.mcast_ifn, ipvs->bcfg.syncid, tinfo->id);

	while (!kthread_should_stop()) {
		wait_event_interruptible(*sk_sleep(tinfo->sock->sk),
			 !skb_queue_empty(&tinfo->sock->sk->sk_receive_queue)
			 || kthread_should_stop());

		/* do we have data now? */
		while (!skb_queue_empty(&(tinfo->sock->sk->sk_receive_queue))) {
			len = ip_vs_receive(tinfo->sock, tinfo->buf,
					ipvs->bcfg.sync_maxlen);
			if (len <= 0) {
				if (len != -EAGAIN)
					pr_err("receiving message error\n");
				break;
			}

			ip_vs_process_message(ipvs, tinfo->buf, len);
		}
	}

	return 0;
}