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
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,struct bpf_prog*,int) ; 
 int /*<<< orphan*/  bpf_prog_fops ; 
 int security_bpf_prog (struct bpf_prog*) ; 

int bpf_prog_new_fd(struct bpf_prog *prog)
{
	int ret;

	ret = security_bpf_prog(prog);
	if (ret < 0)
		return ret;

	return anon_inode_getfd("bpf-prog", &bpf_prog_fops, prog,
				O_RDWR | O_CLOEXEC);
}