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
struct sock_filter {int dummy; } ;
struct bpf_prog {int len; int /*<<< orphan*/  insns; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 struct bpf_prog* ERR_PTR (int) ; 
 int GFP_KERNEL ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  __bpf_prog_release (struct bpf_prog*) ; 
 int bpf_convert_filter (struct sock_filter*,int,struct bpf_prog*,int*,int*) ; 
 struct bpf_prog* bpf_prog_realloc (struct bpf_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_prog* bpf_prog_select_runtime (struct bpf_prog*,int*) ; 
 int /*<<< orphan*/  bpf_prog_size (int) ; 
 int /*<<< orphan*/  kfree (struct sock_filter*) ; 
 struct sock_filter* kmemdup (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static struct bpf_prog *bpf_migrate_filter(struct bpf_prog *fp)
{
	struct sock_filter *old_prog;
	struct bpf_prog *old_fp;
	int err, new_len, old_len = fp->len;
	bool seen_ld_abs = false;

	/* We are free to overwrite insns et al right here as it
	 * won't be used at this point in time anymore internally
	 * after the migration to the internal BPF instruction
	 * representation.
	 */
	BUILD_BUG_ON(sizeof(struct sock_filter) !=
		     sizeof(struct bpf_insn));

	/* Conversion cannot happen on overlapping memory areas,
	 * so we need to keep the user BPF around until the 2nd
	 * pass. At this time, the user BPF is stored in fp->insns.
	 */
	old_prog = kmemdup(fp->insns, old_len * sizeof(struct sock_filter),
			   GFP_KERNEL | __GFP_NOWARN);
	if (!old_prog) {
		err = -ENOMEM;
		goto out_err;
	}

	/* 1st pass: calculate the new program length. */
	err = bpf_convert_filter(old_prog, old_len, NULL, &new_len,
				 &seen_ld_abs);
	if (err)
		goto out_err_free;

	/* Expand fp for appending the new filter representation. */
	old_fp = fp;
	fp = bpf_prog_realloc(old_fp, bpf_prog_size(new_len), 0);
	if (!fp) {
		/* The old_fp is still around in case we couldn't
		 * allocate new memory, so uncharge on that one.
		 */
		fp = old_fp;
		err = -ENOMEM;
		goto out_err_free;
	}

	fp->len = new_len;

	/* 2nd pass: remap sock_filter insns into bpf_insn insns. */
	err = bpf_convert_filter(old_prog, old_len, fp, &new_len,
				 &seen_ld_abs);
	if (err)
		/* 2nd bpf_convert_filter() can fail only if it fails
		 * to allocate memory, remapping must succeed. Note,
		 * that at this time old_fp has already been released
		 * by krealloc().
		 */
		goto out_err_free;

	fp = bpf_prog_select_runtime(fp, &err);
	if (err)
		goto out_err_free;

	kfree(old_prog);
	return fp;

out_err_free:
	kfree(old_prog);
out_err:
	__bpf_prog_release(fp);
	return ERR_PTR(err);
}