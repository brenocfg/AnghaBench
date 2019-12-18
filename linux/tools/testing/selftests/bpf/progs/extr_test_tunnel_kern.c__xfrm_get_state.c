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
typedef  int /*<<< orphan*/  x ;
struct bpf_xfrm_state {int /*<<< orphan*/  remote_ipv4; int /*<<< orphan*/  spi; int /*<<< orphan*/  reqid; } ;
struct __sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  fmt ;

/* Variables and functions */
 int TC_ACT_OK ; 
 int /*<<< orphan*/  bpf_ntohl (int /*<<< orphan*/ ) ; 
 int bpf_skb_get_xfrm_state (struct __sk_buff*,int /*<<< orphan*/ ,struct bpf_xfrm_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_trace_printk (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _xfrm_get_state(struct __sk_buff *skb)
{
	struct bpf_xfrm_state x;
	char fmt[] = "reqid %d spi 0x%x remote ip 0x%x\n";
	int ret;

	ret = bpf_skb_get_xfrm_state(skb, 0, &x, sizeof(x), 0);
	if (ret < 0)
		return TC_ACT_OK;

	bpf_trace_printk(fmt, sizeof(fmt), x.reqid, bpf_ntohl(x.spi),
			 bpf_ntohl(x.remote_ipv4));
	return TC_ACT_OK;
}