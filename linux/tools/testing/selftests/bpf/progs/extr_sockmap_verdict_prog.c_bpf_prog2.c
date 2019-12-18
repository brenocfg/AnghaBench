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
struct __sk_buff {int /*<<< orphan*/  remote_port; int /*<<< orphan*/  local_port; scalar_t__ data; scalar_t__ data_end; } ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int SK_DROP ; 
 int bpf_sk_redirect_map (struct __sk_buff*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_map_rx ; 
 int /*<<< orphan*/  sock_map_tx ; 

int bpf_prog2(struct __sk_buff *skb)
{
	void *data_end = (void *)(long) skb->data_end;
	void *data = (void *)(long) skb->data;
	__u32 lport = skb->local_port;
	__u32 rport = skb->remote_port;
	__u8 *d = data;
	__u8 sk, map;

	if (data + 8 > data_end)
		return SK_DROP;

	map = d[0];
	sk = d[1];

	d[0] = 0xd;
	d[1] = 0xe;
	d[2] = 0xa;
	d[3] = 0xd;
	d[4] = 0xb;
	d[5] = 0xe;
	d[6] = 0xe;
	d[7] = 0xf;

	if (!map)
		return bpf_sk_redirect_map(skb, &sock_map_rx, sk, 0);
	return bpf_sk_redirect_map(skb, &sock_map_tx, sk, 0);
}