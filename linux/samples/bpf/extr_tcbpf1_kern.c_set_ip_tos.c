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
typedef  int /*<<< orphan*/  new_tos ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  IP_CSUM_OFF ; 
 int /*<<< orphan*/  TOS_OFF ; 
 int /*<<< orphan*/  bpf_l3_csum_replace (struct __sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bpf_skb_store_bytes (struct __sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_byte (struct __sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_ip_tos(struct __sk_buff *skb, __u8 new_tos)
{
	__u8 old_tos = load_byte(skb, TOS_OFF);

	bpf_l3_csum_replace(skb, IP_CSUM_OFF, htons(old_tos), htons(new_tos), 2);
	bpf_skb_store_bytes(skb, TOS_OFF, &new_tos, sizeof(new_tos), 0);
}