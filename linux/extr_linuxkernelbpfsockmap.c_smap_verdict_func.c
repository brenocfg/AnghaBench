#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smap_psock {int /*<<< orphan*/ * sock; int /*<<< orphan*/  bpf_verdict; } ;
struct sk_buff {int /*<<< orphan*/ * sk; } ;
struct bpf_prog {int (* bpf_func ) (struct sk_buff*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  insnsi; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sk_redir; } ;
struct TYPE_4__ {TYPE_1__ bpf; } ;

/* Variables and functions */
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
 int SK_PASS ; 
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
 int __SK_DROP ; 
 int __SK_PASS ; 
 int __SK_REDIRECT ; 
 int /*<<< orphan*/  bpf_compute_data_end_sk_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int stub1 (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int smap_verdict_func(struct smap_psock *psock, struct sk_buff *skb)
{
	struct bpf_prog *prog = READ_ONCE(psock->bpf_verdict);
	int rc;

	if (unlikely(!prog))
		return __SK_DROP;

	skb_orphan(skb);
	/* We need to ensure that BPF metadata for maps is also cleared
	 * when we orphan the skb so that we don't have the possibility
	 * to reference a stale map.
	 */
	TCP_SKB_CB(skb)->bpf.sk_redir = NULL;
	skb->sk = psock->sock;
	bpf_compute_data_end_sk_skb(skb);
	preempt_disable();
	rc = (*prog->bpf_func)(skb, prog->insnsi);
	preempt_enable();
	skb->sk = NULL;

	/* Moving return codes from UAPI namespace into internal namespace */
	return rc == SK_PASS ?
		(TCP_SKB_CB(skb)->bpf.sk_redir ? __SK_REDIRECT : __SK_PASS) :
		__SK_DROP;
}