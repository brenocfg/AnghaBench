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
struct sk_buff {int dummy; } ;
struct dst_entry {int dummy; } ;
struct bpf_lwt_prog {int /*<<< orphan*/  name; int /*<<< orphan*/  prog; } ;

/* Variables and functions */
#define  BPF_DROP 131 
#define  BPF_LWT_REROUTE 130 
#define  BPF_OK 129 
#define  BPF_REDIRECT 128 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  bpf_compute_data_pointers (struct sk_buff*) ; 
 int bpf_prog_run_save_cb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_warn_once (char*,...) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int skb_do_redirect (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int run_lwt_bpf(struct sk_buff *skb, struct bpf_lwt_prog *lwt,
		       struct dst_entry *dst, bool can_redirect)
{
	int ret;

	/* Preempt disable is needed to protect per-cpu redirect_info between
	 * BPF prog and skb_do_redirect(). The call_rcu in bpf_prog_put() and
	 * access to maps strictly require a rcu_read_lock() for protection,
	 * mixing with BH RCU lock doesn't work.
	 */
	preempt_disable();
	bpf_compute_data_pointers(skb);
	ret = bpf_prog_run_save_cb(lwt->prog, skb);

	switch (ret) {
	case BPF_OK:
	case BPF_LWT_REROUTE:
		break;

	case BPF_REDIRECT:
		if (unlikely(!can_redirect)) {
			pr_warn_once("Illegal redirect return code in prog %s\n",
				     lwt->name ? : "<unknown>");
			ret = BPF_OK;
		} else {
			skb_reset_mac_header(skb);
			ret = skb_do_redirect(skb);
			if (ret == 0)
				ret = BPF_REDIRECT;
		}
		break;

	case BPF_DROP:
		kfree_skb(skb);
		ret = -EPERM;
		break;

	default:
		pr_warn_once("bpf-lwt: Illegal return value %u, expect packet loss\n", ret);
		kfree_skb(skb);
		ret = -EINVAL;
		break;
	}

	preempt_enable();

	return ret;
}