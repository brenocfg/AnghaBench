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
typedef  int /*<<< orphan*/  cong ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
#define  BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB 130 
#define  BPF_SOCK_OPS_NEEDS_ECN 129 
#define  BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB 128 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_CONGESTION ; 
 int bpf_ntohl (scalar_t__) ; 
 int /*<<< orphan*/  bpf_printk (char*,int) ; 
 int bpf_setsockopt (struct bpf_sock_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int bpf_cong(struct bpf_sock_ops *skops)
{
	char cong[] = "dctcp";
	int rv = 0;
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

	/* Check if both hosts are in the same datacenter. For this
	 * example they are if the 1st 5.5 bytes in the IPv6 address
	 * are the same.
	 */
	if (skops->family == AF_INET6 &&
	    skops->local_ip6[0] == skops->remote_ip6[0] &&
	    (bpf_ntohl(skops->local_ip6[1]) & 0xfff00000) ==
	    (bpf_ntohl(skops->remote_ip6[1]) & 0xfff00000)) {
		switch (op) {
		case BPF_SOCK_OPS_NEEDS_ECN:
			rv = 1;
			break;
		case BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
			rv = bpf_setsockopt(skops, SOL_TCP, TCP_CONGESTION,
					    cong, sizeof(cong));
			break;
		case BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
			rv = bpf_setsockopt(skops, SOL_TCP, TCP_CONGESTION,
					    cong, sizeof(cong));
			break;
		default:
			rv = -1;
		}
	} else {
		rv = -1;
	}
#ifdef DEBUG
	bpf_printk("Returning %d\n", rv);
#endif
	skops->reply = rv;
	return 1;
}