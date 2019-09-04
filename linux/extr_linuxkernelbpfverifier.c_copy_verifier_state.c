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
struct bpf_verifier_state {int curframe; struct bpf_func_state** frame; int /*<<< orphan*/  parent; int /*<<< orphan*/  speculative; } ;
struct bpf_func_state {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int copy_func_state (struct bpf_func_state*,struct bpf_func_state*) ; 
 int /*<<< orphan*/  free_func_state (struct bpf_func_state*) ; 
 struct bpf_func_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copy_verifier_state(struct bpf_verifier_state *dst_state,
			       const struct bpf_verifier_state *src)
{
	struct bpf_func_state *dst;
	int i, err;

	/* if dst has more stack frames then src frame, free them */
	for (i = src->curframe + 1; i <= dst_state->curframe; i++) {
		free_func_state(dst_state->frame[i]);
		dst_state->frame[i] = NULL;
	}
	dst_state->speculative = src->speculative;
	dst_state->curframe = src->curframe;
	dst_state->parent = src->parent;
	for (i = 0; i <= src->curframe; i++) {
		dst = dst_state->frame[i];
		if (!dst) {
			dst = kzalloc(sizeof(*dst), GFP_KERNEL);
			if (!dst)
				return -ENOMEM;
			dst_state->frame[i] = dst;
		}
		err = copy_func_state(dst, src->frame[i]);
		if (err)
			return err;
	}
	return 0;
}