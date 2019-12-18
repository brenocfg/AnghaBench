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
struct fd {int dummy; } ;
struct bpf_prog {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct bpf_prog* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 struct bpf_prog* ____bpf_prog_get (struct fd) ; 
 int /*<<< orphan*/  bpf_prog_get_ok (struct bpf_prog*,int*,int) ; 
 struct bpf_prog* bpf_prog_inc (struct bpf_prog*) ; 
 struct fd fdget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 

__attribute__((used)) static struct bpf_prog *__bpf_prog_get(u32 ufd, enum bpf_prog_type *attach_type,
				       bool attach_drv)
{
	struct fd f = fdget(ufd);
	struct bpf_prog *prog;

	prog = ____bpf_prog_get(f);
	if (IS_ERR(prog))
		return prog;
	if (!bpf_prog_get_ok(prog, attach_type, attach_drv)) {
		prog = ERR_PTR(-EINVAL);
		goto out;
	}

	prog = bpf_prog_inc(prog);
out:
	fdput(f);
	return prog;
}