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
struct bpf_tunnel_key {int /*<<< orphan*/  tunnel_label; int /*<<< orphan*/ * remote_ipv6; int /*<<< orphan*/  tunnel_id; } ;
struct __sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  fmt ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_TUNINFO_IPV6 ; 
 int /*<<< orphan*/  ERROR (int) ; 
 int TC_ACT_OK ; 
 int TC_ACT_SHOT ; 
 int bpf_skb_get_tunnel_key (struct __sk_buff*,struct bpf_tunnel_key*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_trace_printk (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _ip6vxlan_get_tunnel(struct __sk_buff *skb)
{
	char fmt[] = "key %d remote ip6 ::%x label %x\n";
	struct bpf_tunnel_key key;
	int ret;

	ret = bpf_skb_get_tunnel_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (ret < 0) {
		ERROR(ret);
		return TC_ACT_SHOT;
	}

	bpf_trace_printk(fmt, sizeof(fmt),
			 key.tunnel_id, key.remote_ipv6[3], key.tunnel_label);

	return TC_ACT_OK;
}