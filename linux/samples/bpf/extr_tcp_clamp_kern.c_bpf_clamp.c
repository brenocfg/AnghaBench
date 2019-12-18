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
typedef  int /*<<< orphan*/  clamp ;
typedef  int /*<<< orphan*/  bufsize ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
#define  BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB 131 
#define  BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB 130 
#define  BPF_SOCK_OPS_TCP_CONNECT_CB 129 
#define  BPF_SOCK_OPS_TIMEOUT_INIT 128 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  TCP_BPF_SNDCWND_CLAMP ; 
 int bpf_ntohl (scalar_t__) ; 
 int /*<<< orphan*/  bpf_printk (char*,int) ; 
 int bpf_setsockopt (struct bpf_sock_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int bpf_clamp(struct bpf_sock_ops *skops)
{
	int bufsize = 150000;
	int to_init = 10;
	int clamp = 100;
	int rv = 0;
	int op;

	/* For testing purposes, only execute rest of BPF program
	 * if neither port numberis 55601
	 */
	if (bpf_ntohl(skops->remote_port) != 55601 && skops->local_port != 55601) {
		skops->reply = -1;
		return 0;
	}

	op = (int) skops->op;

#ifdef DEBUG
	bpf_printk("BPF command: %d\n", op);
#endif

	/* Check that both hosts are within same datacenter. For this example
	 * it is the case when the first 5.5 bytes of their IPv6 addresses are
	 * the same.
	 */
	if (skops->family == AF_INET6 &&
	    skops->local_ip6[0] == skops->remote_ip6[0] &&
	    (bpf_ntohl(skops->local_ip6[1]) & 0xfff00000) ==
	    (bpf_ntohl(skops->remote_ip6[1]) & 0xfff00000)) {
		switch (op) {
		case BPF_SOCK_OPS_TIMEOUT_INIT:
			rv = to_init;
			break;
		case BPF_SOCK_OPS_TCP_CONNECT_CB:
			/* Set sndbuf and rcvbuf of active connections */
			rv = bpf_setsockopt(skops, SOL_SOCKET, SO_SNDBUF,
					    &bufsize, sizeof(bufsize));
			rv += bpf_setsockopt(skops, SOL_SOCKET,
					     SO_RCVBUF, &bufsize,
					     sizeof(bufsize));
			break;
		case BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
			rv = bpf_setsockopt(skops, SOL_TCP,
					    TCP_BPF_SNDCWND_CLAMP,
					    &clamp, sizeof(clamp));
			break;
		case BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
			/* Set sndbuf and rcvbuf of passive connections */
			rv = bpf_setsockopt(skops, SOL_TCP,
					    TCP_BPF_SNDCWND_CLAMP,
					    &clamp, sizeof(clamp));
			rv += bpf_setsockopt(skops, SOL_SOCKET,
					     SO_SNDBUF, &bufsize,
					     sizeof(bufsize));
			rv += bpf_setsockopt(skops, SOL_SOCKET,
					     SO_RCVBUF, &bufsize,
					     sizeof(bufsize));
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