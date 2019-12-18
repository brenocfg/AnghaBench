#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct rtable {int dummy; } ;
struct ipcm_cookie {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct inet_sock {TYPE_1__ cork; } ;
struct flowi4 {int dummy; } ;

/* Variables and functions */
 unsigned int MSG_PROBE ; 
 int __ip_append_data (struct sock*,struct flowi4*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int (*) (void*,char*,int,int,int,struct sk_buff*),void*,int,int,unsigned int) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int ip_setup_cork (struct sock*,int /*<<< orphan*/ *,struct ipcm_cookie*,struct rtable**) ; 
 int /*<<< orphan*/  sk_page_frag (struct sock*) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 

int ip_append_data(struct sock *sk, struct flowi4 *fl4,
		   int getfrag(void *from, char *to, int offset, int len,
			       int odd, struct sk_buff *skb),
		   void *from, int length, int transhdrlen,
		   struct ipcm_cookie *ipc, struct rtable **rtp,
		   unsigned int flags)
{
	struct inet_sock *inet = inet_sk(sk);
	int err;

	if (flags&MSG_PROBE)
		return 0;

	if (skb_queue_empty(&sk->sk_write_queue)) {
		err = ip_setup_cork(sk, &inet->cork.base, ipc, rtp);
		if (err)
			return err;
	} else {
		transhdrlen = 0;
	}

	return __ip_append_data(sk, fl4, &sk->sk_write_queue, &inet->cork.base,
				sk_page_frag(sk), getfrag,
				from, length, transhdrlen, flags);
}