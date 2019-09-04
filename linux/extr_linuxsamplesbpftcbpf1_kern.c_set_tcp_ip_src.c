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
struct __sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  new_ip ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IP_CSUM_OFF ; 
 int /*<<< orphan*/  IP_SRC_OFF ; 
 int IS_PSEUDO ; 
 int /*<<< orphan*/  TCP_CSUM_OFF ; 
 int /*<<< orphan*/  _htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_l3_csum_replace (struct __sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bpf_l4_csum_replace (struct __sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bpf_skb_store_bytes (struct __sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_word (struct __sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_tcp_ip_src(struct __sk_buff *skb, __u32 new_ip)
{
	__u32 old_ip = _htonl(load_word(skb, IP_SRC_OFF));

	bpf_l4_csum_replace(skb, TCP_CSUM_OFF, old_ip, new_ip, IS_PSEUDO | sizeof(new_ip));
	bpf_l3_csum_replace(skb, IP_CSUM_OFF, old_ip, new_ip, sizeof(new_ip));
	bpf_skb_store_bytes(skb, IP_SRC_OFF, &new_ip, sizeof(new_ip), 0);
}