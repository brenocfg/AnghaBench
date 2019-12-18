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
struct sock_fprog_kern {int /*<<< orphan*/  filter; int /*<<< orphan*/  len; } ;
struct sock_fprog {int /*<<< orphan*/  len; } ;
struct bpf_prog {struct sock_fprog_kern* orig_prog; int /*<<< orphan*/  insns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_NOWARN ; 
 unsigned int bpf_classic_proglen (struct sock_fprog const*) ; 
 int /*<<< orphan*/  kfree (struct sock_fprog_kern*) ; 
 struct sock_fprog_kern* kmalloc (int,int) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int bpf_prog_store_orig_filter(struct bpf_prog *fp,
				      const struct sock_fprog *fprog)
{
	unsigned int fsize = bpf_classic_proglen(fprog);
	struct sock_fprog_kern *fkprog;

	fp->orig_prog = kmalloc(sizeof(*fkprog), GFP_KERNEL);
	if (!fp->orig_prog)
		return -ENOMEM;

	fkprog = fp->orig_prog;
	fkprog->len = fprog->len;

	fkprog->filter = kmemdup(fp->insns, fsize,
				 GFP_KERNEL | __GFP_NOWARN);
	if (!fkprog->filter) {
		kfree(fp->orig_prog);
		return -ENOMEM;
	}

	return 0;
}