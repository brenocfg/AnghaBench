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
struct bpf_prog_aux {int /*<<< orphan*/  ksym_lnode; struct bpf_prog* prog; } ;
struct bpf_prog {unsigned int pages; struct bpf_prog_aux* aux; int /*<<< orphan*/  jit_requested; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD_RCU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 int __GFP_ZERO ; 
 struct bpf_prog* __vmalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebpf_jit_enabled () ; 
 struct bpf_prog_aux* kzalloc (int,int) ; 
 unsigned int round_up (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vfree (struct bpf_prog*) ; 

struct bpf_prog *bpf_prog_alloc_no_stats(unsigned int size, gfp_t gfp_extra_flags)
{
	gfp_t gfp_flags = GFP_KERNEL | __GFP_ZERO | gfp_extra_flags;
	struct bpf_prog_aux *aux;
	struct bpf_prog *fp;

	size = round_up(size, PAGE_SIZE);
	fp = __vmalloc(size, gfp_flags, PAGE_KERNEL);
	if (fp == NULL)
		return NULL;

	aux = kzalloc(sizeof(*aux), GFP_KERNEL | gfp_extra_flags);
	if (aux == NULL) {
		vfree(fp);
		return NULL;
	}

	fp->pages = size / PAGE_SIZE;
	fp->aux = aux;
	fp->aux->prog = fp;
	fp->jit_requested = ebpf_jit_enabled();

	INIT_LIST_HEAD_RCU(&fp->aux->ksym_lnode);

	return fp;
}