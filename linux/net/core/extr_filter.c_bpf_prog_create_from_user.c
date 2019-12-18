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
struct bpf_prog {int /*<<< orphan*/ * orig_prog; int /*<<< orphan*/  len; int /*<<< orphan*/  insns; } ;
typedef  int /*<<< orphan*/  bpf_aux_classic_check_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int PTR_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  __bpf_prog_free (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_check_basics_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int bpf_classic_proglen (struct sock_fprog*) ; 
 struct bpf_prog* bpf_prepare_filter (struct bpf_prog*,int /*<<< orphan*/ ) ; 
 struct bpf_prog* bpf_prog_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_size (int /*<<< orphan*/ ) ; 
 int bpf_prog_store_orig_filter (struct bpf_prog*,struct sock_fprog*) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int bpf_prog_create_from_user(struct bpf_prog **pfp, struct sock_fprog *fprog,
			      bpf_aux_classic_check_t trans, bool save_orig)
{
	unsigned int fsize = bpf_classic_proglen(fprog);
	struct bpf_prog *fp;
	int err;

	/* Make sure new filter is there and in the right amounts. */
	if (!bpf_check_basics_ok(fprog->filter, fprog->len))
		return -EINVAL;

	fp = bpf_prog_alloc(bpf_prog_size(fprog->len), 0);
	if (!fp)
		return -ENOMEM;

	if (copy_from_user(fp->insns, fprog->filter, fsize)) {
		__bpf_prog_free(fp);
		return -EFAULT;
	}

	fp->len = fprog->len;
	fp->orig_prog = NULL;

	if (save_orig) {
		err = bpf_prog_store_orig_filter(fp, fprog);
		if (err) {
			__bpf_prog_free(fp);
			return -ENOMEM;
		}
	}

	/* bpf_prepare_filter() already takes care of freeing
	 * memory in case something goes wrong.
	 */
	fp = bpf_prepare_filter(fp, trans);
	if (IS_ERR(fp))
		return PTR_ERR(fp);

	*pfp = fp;
	return 0;
}