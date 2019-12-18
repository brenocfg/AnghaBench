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
typedef  int /*<<< orphan*/  tos ;
struct ipv6hdr {int priority; int* flow_lbl; } ;
struct iphdr {int tos; } ;
struct bpf_sock_ops {int reply; int /*<<< orphan*/  family; scalar_t__ op; } ;
typedef  int /*<<< orphan*/  save_syn ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
#define  BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB 129 
#define  BPF_SOCK_OPS_TCP_LISTEN_CB 128 
 int /*<<< orphan*/  IPV6_TCLASS ; 
 int /*<<< orphan*/  IP_TOS ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  SOL_IPV6 ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_SAVED_SYN ; 
 int /*<<< orphan*/  TCP_SAVE_SYN ; 
 int bpf_getsockopt (struct bpf_sock_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bpf_printk (char*,int) ; 
 int bpf_setsockopt (struct bpf_sock_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int bpf_basertt(struct bpf_sock_ops *skops)
{
	char header[sizeof(struct ipv6hdr)];
	struct ipv6hdr *hdr6;
	struct iphdr *hdr;
	int hdr_size = 0;
	int save_syn = 1;
	int tos = 0;
	int rv = 0;
	int op;

	op = (int) skops->op;

#ifdef DEBUG
	bpf_printk("BPF command: %d\n", op);
#endif
	switch (op) {
	case BPF_SOCK_OPS_TCP_LISTEN_CB:
		rv = bpf_setsockopt(skops, SOL_TCP, TCP_SAVE_SYN,
				   &save_syn, sizeof(save_syn));
		break;
	case BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
		if (skops->family == AF_INET)
			hdr_size = sizeof(struct iphdr);
		else
			hdr_size = sizeof(struct ipv6hdr);
		rv = bpf_getsockopt(skops, SOL_TCP, TCP_SAVED_SYN,
				    header, hdr_size);
		if (!rv) {
			if (skops->family == AF_INET) {
				hdr = (struct iphdr *) header;
				tos = hdr->tos;
				if (tos != 0)
					bpf_setsockopt(skops, SOL_IP, IP_TOS,
						       &tos, sizeof(tos));
			} else {
				hdr6 = (struct ipv6hdr *) header;
				tos = ((hdr6->priority) << 4 |
				       (hdr6->flow_lbl[0]) >>  4);
				if (tos)
					bpf_setsockopt(skops, SOL_IPV6,
						       IPV6_TCLASS,
						       &tos, sizeof(tos));
			}
			rv = 0;
		}
		break;
	default:
		rv = -1;
	}
#ifdef DEBUG
	bpf_printk("Returning %d\n", rv);
#endif
	skops->reply = rv;
	return 1;
}