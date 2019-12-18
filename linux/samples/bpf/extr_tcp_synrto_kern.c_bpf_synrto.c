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
struct bpf_sock_ops {scalar_t__ remote_port; int local_port; int reply; scalar_t__ family; scalar_t__* local_ip6; scalar_t__* remote_ip6; scalar_t__ op; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int BPF_SOCK_OPS_TIMEOUT_INIT ; 
 int bpf_ntohl (scalar_t__) ; 
 int /*<<< orphan*/  bpf_printk (char*,int) ; 

int bpf_synrto(struct bpf_sock_ops *skops)
{
	int rv = -1;
	int op;

	/* For testing purposes, only execute rest of BPF program
	 * if neither port numberis 55601
	 */
	if (bpf_ntohl(skops->remote_port) != 55601 &&
	    skops->local_port != 55601) {
		skops->reply = -1;
		return 1;
	}

	op = (int) skops->op;

#ifdef DEBUG
	bpf_printk("BPF command: %d\n", op);
#endif

	/* Check for TIMEOUT_INIT operation and IPv6 addresses */
	if (op == BPF_SOCK_OPS_TIMEOUT_INIT &&
		skops->family == AF_INET6) {

		/* If the first 5.5 bytes of the IPv6 address are the same
		 * then both hosts are in the same datacenter
		 * so use an RTO of 10ms
		 */
		if (skops->local_ip6[0] == skops->remote_ip6[0] &&
		    (bpf_ntohl(skops->local_ip6[1]) & 0xfff00000) ==
		    (bpf_ntohl(skops->remote_ip6[1]) & 0xfff00000))
			rv = 10;
	}
#ifdef DEBUG
	bpf_printk("Returning %d\n", rv);
#endif
	skops->reply = rv;
	return 1;
}