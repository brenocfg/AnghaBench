#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct bpf_prog {unsigned int pages; TYPE_1__* aux; } ;
typedef  int gfp_t ;
struct TYPE_2__ {struct bpf_prog* prog; int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 int __GFP_ZERO ; 
 int __bpf_prog_charge (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  __bpf_prog_free (struct bpf_prog*) ; 
 int /*<<< orphan*/  __bpf_prog_uncharge (int /*<<< orphan*/ ,unsigned int) ; 
 struct bpf_prog* __vmalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct bpf_prog*,struct bpf_prog*,unsigned int) ; 
 unsigned int round_up (unsigned int,unsigned int) ; 

struct bpf_prog *bpf_prog_realloc(struct bpf_prog *fp_old, unsigned int size,
				  gfp_t gfp_extra_flags)
{
	gfp_t gfp_flags = GFP_KERNEL | __GFP_ZERO | gfp_extra_flags;
	struct bpf_prog *fp;
	u32 pages, delta;
	int ret;

	BUG_ON(fp_old == NULL);

	size = round_up(size, PAGE_SIZE);
	pages = size / PAGE_SIZE;
	if (pages <= fp_old->pages)
		return fp_old;

	delta = pages - fp_old->pages;
	ret = __bpf_prog_charge(fp_old->aux->user, delta);
	if (ret)
		return NULL;

	fp = __vmalloc(size, gfp_flags, PAGE_KERNEL);
	if (fp == NULL) {
		__bpf_prog_uncharge(fp_old->aux->user, delta);
	} else {
		memcpy(fp, fp_old, fp_old->pages * PAGE_SIZE);
		fp->pages = pages;
		fp->aux->prog = fp;

		/* We keep fp->aux from fp_old around in the new
		 * reallocated structure.
		 */
		fp_old->aux = NULL;
		__bpf_prog_free(fp_old);
	}

	return fp;
}