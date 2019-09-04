#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct rt6_info {int dummy; } ;
struct ipcm6_cookie {scalar_t__ dontfrag; TYPE_1__* opt; } ;
struct TYPE_8__ {int /*<<< orphan*/ * dst; int /*<<< orphan*/ * opt; scalar_t__ addr; scalar_t__ flags; } ;
struct inet_cork_full {TYPE_4__ base; } ;
struct inet6_cork {int /*<<< orphan*/ * opt; } ;
struct flowi6 {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  task_frag; } ;
struct TYPE_6__ {scalar_t__ dontfrag; } ;
struct TYPE_5__ {int opt_flen; } ;

/* Variables and functions */
 struct sk_buff* ERR_PTR (int) ; 
 unsigned int MSG_PROBE ; 
 int __ip6_append_data (struct sock*,struct flowi6*,struct sk_buff_head*,TYPE_4__*,struct inet6_cork*,int /*<<< orphan*/ *,int (*) (void*,char*,int,int,int,struct sk_buff*),void*,int,int,unsigned int,struct ipcm6_cookie*) ; 
 int /*<<< orphan*/  __ip6_flush_pending_frames (struct sock*,struct sk_buff_head*,struct inet_cork_full*,struct inet6_cork*) ; 
 struct sk_buff* __ip6_make_skb (struct sock*,struct sk_buff_head*,struct inet_cork_full*,struct inet6_cork*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 TYPE_3__* current ; 
 TYPE_2__* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_cork_release (struct inet_cork_full*,struct inet6_cork*) ; 
 int ip6_setup_cork (struct sock*,struct inet_cork_full*,struct inet6_cork*,struct ipcm6_cookie*,struct rt6_info*,struct flowi6*) ; 

struct sk_buff *ip6_make_skb(struct sock *sk,
			     int getfrag(void *from, char *to, int offset,
					 int len, int odd, struct sk_buff *skb),
			     void *from, int length, int transhdrlen,
			     struct ipcm6_cookie *ipc6, struct flowi6 *fl6,
			     struct rt6_info *rt, unsigned int flags,
			     struct inet_cork_full *cork)
{
	struct inet6_cork v6_cork;
	struct sk_buff_head queue;
	int exthdrlen = (ipc6->opt ? ipc6->opt->opt_flen : 0);
	int err;

	if (flags & MSG_PROBE)
		return NULL;

	__skb_queue_head_init(&queue);

	cork->base.flags = 0;
	cork->base.addr = 0;
	cork->base.opt = NULL;
	cork->base.dst = NULL;
	v6_cork.opt = NULL;
	err = ip6_setup_cork(sk, cork, &v6_cork, ipc6, rt, fl6);
	if (err) {
		ip6_cork_release(cork, &v6_cork);
		return ERR_PTR(err);
	}
	if (ipc6->dontfrag < 0)
		ipc6->dontfrag = inet6_sk(sk)->dontfrag;

	err = __ip6_append_data(sk, fl6, &queue, &cork->base, &v6_cork,
				&current->task_frag, getfrag, from,
				length + exthdrlen, transhdrlen + exthdrlen,
				flags, ipc6);
	if (err) {
		__ip6_flush_pending_frames(sk, &queue, cork, &v6_cork);
		return ERR_PTR(err);
	}

	return __ip6_make_skb(sk, &queue, cork, &v6_cork);
}