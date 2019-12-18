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
struct __sk_buff {int len; scalar_t__ data; scalar_t__ data_end; scalar_t__ remote_port; scalar_t__ local_port; } ;
typedef  int __u8 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int SK_DROP ; 
 int bpf_skb_pull_data (struct __sk_buff*,int) ; 

int bpf_prog1(struct __sk_buff *skb)
{
	void *data_end = (void *)(long) skb->data_end;
	void *data = (void *)(long) skb->data;
	__u32 lport = skb->local_port;
	__u32 rport = skb->remote_port;
	__u8 *d = data;
	__u32 len = (__u32) data_end - (__u32) data;
	int err;

	if (data + 10 > data_end) {
		err = bpf_skb_pull_data(skb, 10);
		if (err)
			return SK_DROP;

		data_end = (void *)(long)skb->data_end;
		data = (void *)(long)skb->data;
		if (data + 10 > data_end)
			return SK_DROP;
	}

	/* This write/read is a bit pointless but tests the verifier and
	 * strparser handler for read/write pkt data and access into sk
	 * fields.
	 */
	d = data;
	d[7] = 1;
	return skb->len;
}