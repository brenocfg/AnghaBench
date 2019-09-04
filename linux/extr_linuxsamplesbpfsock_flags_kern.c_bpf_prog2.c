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
struct bpf_sock {int /*<<< orphan*/  protocol; int /*<<< orphan*/  type; int /*<<< orphan*/  family; } ;
typedef  int /*<<< orphan*/  fmt ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_ICMP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  bpf_trace_printk (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bpf_prog2(struct bpf_sock *sk)
{
	char fmt[] = "socket: family %d type %d protocol %d\n";

	bpf_trace_printk(fmt, sizeof(fmt), sk->family, sk->type, sk->protocol);

	/* block PF_INET, SOCK_RAW, IPPROTO_ICMP sockets
	 * ie., make ping fail
	 */
	if (sk->family == PF_INET &&
	    sk->type == SOCK_RAW  &&
	    sk->protocol == IPPROTO_ICMP)
		return 0;

	return 1;
}