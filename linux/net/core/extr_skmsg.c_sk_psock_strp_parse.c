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
struct strparser {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  skb_parser; } ;
struct sk_psock {TYPE_1__ progs; } ;
struct sk_buff {int len; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct bpf_prog*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int sk_psock_bpf_run (struct sk_psock*,struct bpf_prog*,struct sk_buff*) ; 
 struct sk_psock* sk_psock_from_strp (struct strparser*) ; 

__attribute__((used)) static int sk_psock_strp_parse(struct strparser *strp, struct sk_buff *skb)
{
	struct sk_psock *psock = sk_psock_from_strp(strp);
	struct bpf_prog *prog;
	int ret = skb->len;

	rcu_read_lock();
	prog = READ_ONCE(psock->progs.skb_parser);
	if (likely(prog))
		ret = sk_psock_bpf_run(psock, prog, skb);
	rcu_read_unlock();
	return ret;
}