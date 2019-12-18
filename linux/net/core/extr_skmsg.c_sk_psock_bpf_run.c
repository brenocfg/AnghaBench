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
struct sk_psock {int /*<<< orphan*/ * sk; } ;
struct sk_buff {int /*<<< orphan*/ * sk; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int BPF_PROG_RUN (struct bpf_prog*,struct sk_buff*) ; 
 int /*<<< orphan*/  bpf_compute_data_end_sk_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static int sk_psock_bpf_run(struct sk_psock *psock, struct bpf_prog *prog,
			    struct sk_buff *skb)
{
	int ret;

	skb->sk = psock->sk;
	bpf_compute_data_end_sk_skb(skb);
	preempt_disable();
	ret = BPF_PROG_RUN(prog, skb);
	preempt_enable();
	/* strparser clones the skb before handing it to a upper layer,
	 * meaning skb_orphan has been called. We NULL sk on the way out
	 * to ensure we don't trigger a BUG_ON() in skb/sk operations
	 * later and because we are not charging the memory of this skb
	 * to any socket yet.
	 */
	skb->sk = NULL;
	return ret;
}