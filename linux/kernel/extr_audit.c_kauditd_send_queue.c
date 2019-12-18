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
struct sk_buff_head {int dummy; } ;
typedef  struct sk_buff sk_buff ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int EPERM ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_head (struct sk_buff_head*,struct sk_buff*) ; 
 void stub1 (struct sk_buff*) ; 
 void stub2 (struct sk_buff*) ; 
 void stub3 (struct sk_buff*) ; 

__attribute__((used)) static int kauditd_send_queue(struct sock *sk, u32 portid,
			      struct sk_buff_head *queue,
			      unsigned int retry_limit,
			      void (*skb_hook)(struct sk_buff *skb),
			      void (*err_hook)(struct sk_buff *skb))
{
	int rc = 0;
	struct sk_buff *skb;
	static unsigned int failed = 0;

	/* NOTE: kauditd_thread takes care of all our locking, we just use
	 *       the netlink info passed to us (e.g. sk and portid) */

	while ((skb = skb_dequeue(queue))) {
		/* call the skb_hook for each skb we touch */
		if (skb_hook)
			(*skb_hook)(skb);

		/* can we send to anyone via unicast? */
		if (!sk) {
			if (err_hook)
				(*err_hook)(skb);
			continue;
		}

		/* grab an extra skb reference in case of error */
		skb_get(skb);
		rc = netlink_unicast(sk, skb, portid, 0);
		if (rc < 0) {
			/* fatal failure for our queue flush attempt? */
			if (++failed >= retry_limit ||
			    rc == -ECONNREFUSED || rc == -EPERM) {
				/* yes - error processing for the queue */
				sk = NULL;
				if (err_hook)
					(*err_hook)(skb);
				if (!skb_hook)
					goto out;
				/* keep processing with the skb_hook */
				continue;
			} else
				/* no - requeue to preserve ordering */
				skb_queue_head(queue, skb);
		} else {
			/* it worked - drop the extra reference and continue */
			consume_skb(skb);
			failed = 0;
		}
	}

out:
	return (rc >= 0 ? 0 : rc);
}