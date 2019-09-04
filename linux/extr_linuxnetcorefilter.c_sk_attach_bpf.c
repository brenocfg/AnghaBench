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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int PTR_ERR (struct bpf_prog*) ; 
 struct bpf_prog* __get_bpf (int /*<<< orphan*/ ,struct sock*) ; 
 int __sk_attach_prog (struct bpf_prog*,struct sock*) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 

int sk_attach_bpf(u32 ufd, struct sock *sk)
{
	struct bpf_prog *prog = __get_bpf(ufd, sk);
	int err;

	if (IS_ERR(prog))
		return PTR_ERR(prog);

	err = __sk_attach_prog(prog, sk);
	if (err < 0) {
		bpf_prog_put(prog);
		return err;
	}

	return 0;
}