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
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_SOCKET_FILTER ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int PTR_ERR (struct bpf_prog*) ; 
 struct bpf_prog* bpf_prog_get_type (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __bpf_mt_check_fd(int fd, struct bpf_prog **ret)
{
	struct bpf_prog *prog;

	prog = bpf_prog_get_type(fd, BPF_PROG_TYPE_SOCKET_FILTER);
	if (IS_ERR(prog))
		return PTR_ERR(prog);

	*ret = prog;
	return 0;
}