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
struct bpf_prog {TYPE_1__* aux; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int BPF_MAX_REFCNT ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOENT ; 
 struct bpf_prog* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bpf_prog_put (struct bpf_prog*,int) ; 
 int atomic_fetch_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

struct bpf_prog *bpf_prog_inc_not_zero(struct bpf_prog *prog)
{
	int refold;

	refold = atomic_fetch_add_unless(&prog->aux->refcnt, 1, 0);

	if (refold >= BPF_MAX_REFCNT) {
		__bpf_prog_put(prog, false);
		return ERR_PTR(-EBUSY);
	}

	if (!refold)
		return ERR_PTR(-ENOENT);

	return prog;
}