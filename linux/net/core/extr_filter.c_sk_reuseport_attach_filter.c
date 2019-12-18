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
struct sock_fprog {int dummy; } ;
struct sock {int dummy; } ;
struct bpf_prog {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int PTR_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  __bpf_prog_release (struct bpf_prog*) ; 
 struct bpf_prog* __get_filter (struct sock_fprog*,struct sock*) ; 
 scalar_t__ bpf_prog_size (int /*<<< orphan*/ ) ; 
 int reuseport_attach_prog (struct sock*,struct bpf_prog*) ; 
 scalar_t__ sysctl_optmem_max ; 

int sk_reuseport_attach_filter(struct sock_fprog *fprog, struct sock *sk)
{
	struct bpf_prog *prog = __get_filter(fprog, sk);
	int err;

	if (IS_ERR(prog))
		return PTR_ERR(prog);

	if (bpf_prog_size(prog->len) > sysctl_optmem_max)
		err = -ENOMEM;
	else
		err = reuseport_attach_prog(sk, prog);

	if (err)
		__bpf_prog_release(prog);

	return err;
}