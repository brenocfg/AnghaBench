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
struct sock_fprog_kern {int /*<<< orphan*/  len; int /*<<< orphan*/  filter; } ;
struct bpf_prog {int /*<<< orphan*/ * orig_prog; int /*<<< orphan*/  len; int /*<<< orphan*/  insns; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int PTR_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_check_basics_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int bpf_classic_proglen (struct sock_fprog_kern*) ; 
 struct bpf_prog* bpf_prepare_filter (struct bpf_prog*,int /*<<< orphan*/ *) ; 
 struct bpf_prog* bpf_prog_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int bpf_prog_create(struct bpf_prog **pfp, struct sock_fprog_kern *fprog)
{
	unsigned int fsize = bpf_classic_proglen(fprog);
	struct bpf_prog *fp;

	/* Make sure new filter is there and in the right amounts. */
	if (!bpf_check_basics_ok(fprog->filter, fprog->len))
		return -EINVAL;

	fp = bpf_prog_alloc(bpf_prog_size(fprog->len), 0);
	if (!fp)
		return -ENOMEM;

	memcpy(fp->insns, fprog->filter, fsize);

	fp->len = fprog->len;
	/* Since unattached filters are not copied back to user
	 * space through sk_get_filter(), we do not need to hold
	 * a copy here, and can spare us the work.
	 */
	fp->orig_prog = NULL;

	/* bpf_prepare_filter() already takes care of freeing
	 * memory in case something goes wrong.
	 */
	fp = bpf_prepare_filter(fp, NULL);
	if (IS_ERR(fp))
		return PTR_ERR(fp);

	*pfp = fp;
	return 0;
}