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
struct sk_buff {int dummy; } ;
struct dst_entry {TYPE_3__* lwtstate; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {scalar_t__ prog; } ;
struct bpf_lwt {TYPE_1__ out; TYPE_2__ in; } ;
struct TYPE_6__ {int (* orig_input ) (struct sk_buff*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NO_REDIRECT ; 
 struct bpf_lwt* bpf_lwt_lwtunnel (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ) ; 
 int run_lwt_bpf (struct sk_buff*,TYPE_2__*,struct dst_entry*,int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_input(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct bpf_lwt *bpf;
	int ret;

	bpf = bpf_lwt_lwtunnel(dst->lwtstate);
	if (bpf->in.prog) {
		ret = run_lwt_bpf(skb, &bpf->in, dst, NO_REDIRECT);
		if (ret < 0)
			return ret;
	}

	if (unlikely(!dst->lwtstate->orig_input)) {
		pr_warn_once("orig_input not set on dst for prog %s\n",
			     bpf->out.name);
		kfree_skb(skb);
		return -EINVAL;
	}

	return dst->lwtstate->orig_input(skb);
}