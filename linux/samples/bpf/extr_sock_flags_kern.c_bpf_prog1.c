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
typedef  int /*<<< orphan*/  fmt2 ;
typedef  int /*<<< orphan*/  fmt ;
typedef  int __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int bpf_get_current_uid_gid () ; 
 int /*<<< orphan*/  bpf_trace_printk (char*,int,int,int,...) ; 

int bpf_prog1(struct bpf_sock *sk)
{
	char fmt[] = "socket: family %d type %d protocol %d\n";
	char fmt2[] = "socket: uid %u gid %u\n";
	__u64 gid_uid = bpf_get_current_uid_gid();
	__u32 uid = gid_uid & 0xffffffff;
	__u32 gid = gid_uid >> 32;

	bpf_trace_printk(fmt, sizeof(fmt), sk->family, sk->type, sk->protocol);
	bpf_trace_printk(fmt2, sizeof(fmt2), uid, gid);

	/* block PF_INET6, SOCK_RAW, IPPROTO_ICMPV6 sockets
	 * ie., make ping6 fail
	 */
	if (sk->family == PF_INET6 &&
	    sk->type == SOCK_RAW   &&
	    sk->protocol == IPPROTO_ICMPV6)
		return 0;

	return 1;
}