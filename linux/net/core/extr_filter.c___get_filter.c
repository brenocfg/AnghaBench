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
struct sock_fprog {int /*<<< orphan*/  len; int /*<<< orphan*/  filter; } ;
struct sock {int dummy; } ;
struct bpf_prog {int /*<<< orphan*/  len; int /*<<< orphan*/  insns; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EPERM ; 
 struct bpf_prog* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_FILTER_LOCKED ; 
 int /*<<< orphan*/  __bpf_prog_free (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_check_basics_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int bpf_classic_proglen (struct sock_fprog*) ; 
 struct bpf_prog* bpf_prepare_filter (struct bpf_prog*,int /*<<< orphan*/ *) ; 
 struct bpf_prog* bpf_prog_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_size (int /*<<< orphan*/ ) ; 
 int bpf_prog_store_orig_filter (struct bpf_prog*,struct sock_fprog*) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
struct bpf_prog *__get_filter(struct sock_fprog *fprog, struct sock *sk)
{
	unsigned int fsize = bpf_classic_proglen(fprog);
	struct bpf_prog *prog;
	int err;

	if (sock_flag(sk, SOCK_FILTER_LOCKED))
		return ERR_PTR(-EPERM);

	/* Make sure new filter is there and in the right amounts. */
	if (!bpf_check_basics_ok(fprog->filter, fprog->len))
		return ERR_PTR(-EINVAL);

	prog = bpf_prog_alloc(bpf_prog_size(fprog->len), 0);
	if (!prog)
		return ERR_PTR(-ENOMEM);

	if (copy_from_user(prog->insns, fprog->filter, fsize)) {
		__bpf_prog_free(prog);
		return ERR_PTR(-EFAULT);
	}

	prog->len = fprog->len;

	err = bpf_prog_store_orig_filter(prog, fprog);
	if (err) {
		__bpf_prog_free(prog);
		return ERR_PTR(-ENOMEM);
	}

	/* bpf_prepare_filter() already takes care of freeing
	 * memory in case something goes wrong.
	 */
	return bpf_prepare_filter(prog, NULL);
}