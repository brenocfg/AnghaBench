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
struct socket {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct hidp_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*) ; 
 int EAGAIN ; 
 int hidp_send_frame (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidp_session_terminate (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_set_timer (struct hidp_session*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_head (struct sk_buff_head*,struct sk_buff*) ; 

__attribute__((used)) static void hidp_process_transmit(struct hidp_session *session,
				  struct sk_buff_head *transmit,
				  struct socket *sock)
{
	struct sk_buff *skb;
	int ret;

	BT_DBG("session %p", session);

	while ((skb = skb_dequeue(transmit))) {
		ret = hidp_send_frame(sock, skb->data, skb->len);
		if (ret == -EAGAIN) {
			skb_queue_head(transmit, skb);
			break;
		} else if (ret < 0) {
			hidp_session_terminate(session);
			kfree_skb(skb);
			break;
		}

		hidp_set_timer(session);
		kfree_skb(skb);
	}
}