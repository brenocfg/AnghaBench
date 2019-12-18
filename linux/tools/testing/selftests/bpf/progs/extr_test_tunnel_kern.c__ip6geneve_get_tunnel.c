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
struct geneve_opt {int /*<<< orphan*/  opt_class; } ;
struct bpf_tunnel_key {int /*<<< orphan*/  remote_ipv4; int /*<<< orphan*/  tunnel_id; } ;
struct __sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  gopt ;
typedef  int /*<<< orphan*/  fmt ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_TUNINFO_IPV6 ; 
 int /*<<< orphan*/  ERROR (int) ; 
 int TC_ACT_OK ; 
 int TC_ACT_SHOT ; 
 int bpf_skb_get_tunnel_key (struct __sk_buff*,struct bpf_tunnel_key*,int,int /*<<< orphan*/ ) ; 
 int bpf_skb_get_tunnel_opt (struct __sk_buff*,struct geneve_opt*,int) ; 
 int /*<<< orphan*/  bpf_trace_printk (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _ip6geneve_get_tunnel(struct __sk_buff *skb)
{
	char fmt[] = "key %d remote ip 0x%x geneve class 0x%x\n";
	struct bpf_tunnel_key key;
	struct geneve_opt gopt;
	int ret;

	ret = bpf_skb_get_tunnel_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (ret < 0) {
		ERROR(ret);
		return TC_ACT_SHOT;
	}

	ret = bpf_skb_get_tunnel_opt(skb, &gopt, sizeof(gopt));
	if (ret < 0) {
		ERROR(ret);
		return TC_ACT_SHOT;
	}

	bpf_trace_printk(fmt, sizeof(fmt),
			key.tunnel_id, key.remote_ipv4, gopt.opt_class);

	return TC_ACT_OK;
}