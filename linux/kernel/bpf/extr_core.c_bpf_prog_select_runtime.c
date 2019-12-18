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
struct bpf_prog {int /*<<< orphan*/  jited; int /*<<< orphan*/  aux; scalar_t__ bpf_func; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int bpf_check_tail_call (struct bpf_prog*) ; 
 struct bpf_prog* bpf_int_jit_compile (struct bpf_prog*) ; 
 int bpf_prog_alloc_jited_linfo (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_free_jited_linfo (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_free_unused_jited_linfo (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_is_dev_bound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_lock_ro (struct bpf_prog*) ; 
 int bpf_prog_offload_compile (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_select_func (struct bpf_prog*) ; 

struct bpf_prog *bpf_prog_select_runtime(struct bpf_prog *fp, int *err)
{
	/* In case of BPF to BPF calls, verifier did all the prep
	 * work with regards to JITing, etc.
	 */
	if (fp->bpf_func)
		goto finalize;

	bpf_prog_select_func(fp);

	/* eBPF JITs can rewrite the program in case constant
	 * blinding is active. However, in case of error during
	 * blinding, bpf_int_jit_compile() must always return a
	 * valid program, which in this case would simply not
	 * be JITed, but falls back to the interpreter.
	 */
	if (!bpf_prog_is_dev_bound(fp->aux)) {
		*err = bpf_prog_alloc_jited_linfo(fp);
		if (*err)
			return fp;

		fp = bpf_int_jit_compile(fp);
		if (!fp->jited) {
			bpf_prog_free_jited_linfo(fp);
#ifdef CONFIG_BPF_JIT_ALWAYS_ON
			*err = -ENOTSUPP;
			return fp;
#endif
		} else {
			bpf_prog_free_unused_jited_linfo(fp);
		}
	} else {
		*err = bpf_prog_offload_compile(fp);
		if (*err)
			return fp;
	}

finalize:
	bpf_prog_lock_ro(fp);

	/* The tail call compatibility check can only be done at
	 * this late stage as we need to determine, if we deal
	 * with JITed or non JITed program concatenations and not
	 * all eBPF JITs might immediately support all features.
	 */
	*err = bpf_check_tail_call(fp);

	return fp;
}