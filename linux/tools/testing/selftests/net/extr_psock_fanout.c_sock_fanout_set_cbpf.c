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
struct sock_fprog {int len; struct sock_filter* filter; } ;
struct sock_filter {int dummy; } ;
typedef  int /*<<< orphan*/  bpf_prog ;
typedef  int /*<<< orphan*/  bpf_filter ;

/* Variables and functions */
 scalar_t__ BPF_A ; 
 scalar_t__ BPF_ABS ; 
 scalar_t__ BPF_B ; 
 scalar_t__ BPF_LD ; 
 scalar_t__ BPF_RET ; 
 struct sock_filter BPF_STMT (scalar_t__,int) ; 
 int /*<<< orphan*/  PACKET_FANOUT_DATA ; 
 int /*<<< orphan*/  SOL_PACKET ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock_fprog*,int) ; 

__attribute__((used)) static void sock_fanout_set_cbpf(int fd)
{
	struct sock_filter bpf_filter[] = {
		BPF_STMT(BPF_LD+BPF_B+BPF_ABS, 80),	      /* ldb [80] */
		BPF_STMT(BPF_RET+BPF_A, 0),		      /* ret A */
	};
	struct sock_fprog bpf_prog;

	bpf_prog.filter = bpf_filter;
	bpf_prog.len = sizeof(bpf_filter) / sizeof(struct sock_filter);

	if (setsockopt(fd, SOL_PACKET, PACKET_FANOUT_DATA, &bpf_prog,
		       sizeof(bpf_prog))) {
		perror("fanout data cbpf");
		exit(1);
	}
}