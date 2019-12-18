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
struct bpf_sock_ops {int local_port; int reply; scalar_t__ op; int /*<<< orphan*/  remote_port; } ;
typedef  int /*<<< orphan*/  iw ;
typedef  int /*<<< orphan*/  bufsize ;

/* Variables and functions */
#define  BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB 131 
#define  BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB 130 
#define  BPF_SOCK_OPS_RWND_INIT 129 
#define  BPF_SOCK_OPS_TCP_CONNECT_CB 128 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  TCP_BPF_IW ; 
 int bpf_ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_printk (char*,int) ; 
 int bpf_setsockopt (struct bpf_sock_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int bpf_iw(struct bpf_sock_ops *skops)
{
	int bufsize = 1500000;
	int rwnd_init = 40;
	int iw = 40;
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

	/* Usually there would be a check to insure the hosts are far
	 * from each other so it makes sense to increase buffer sizes
	 */
	switch (op) {
	case BPF_SOCK_OPS_RWND_INIT:
		rv = rwnd_init;
		break;
	case BPF_SOCK_OPS_TCP_CONNECT_CB:
		/* Set sndbuf and rcvbuf of active connections */
		rv = bpf_setsockopt(skops, SOL_SOCKET, SO_SNDBUF, &bufsize,
				    sizeof(bufsize));
		rv += bpf_setsockopt(skops, SOL_SOCKET, SO_RCVBUF,
				     &bufsize, sizeof(bufsize));
		break;
	case BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
		rv = bpf_setsockopt(skops, SOL_TCP, TCP_BPF_IW, &iw,
				    sizeof(iw));
		break;
	case BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
		/* Set sndbuf and rcvbuf of passive connections */
		rv = bpf_setsockopt(skops, SOL_SOCKET, SO_SNDBUF, &bufsize,
				    sizeof(bufsize));
		rv +=  bpf_setsockopt(skops, SOL_SOCKET, SO_RCVBUF,
				      &bufsize, sizeof(bufsize));
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