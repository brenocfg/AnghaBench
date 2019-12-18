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
 scalar_t__ BPF_MAX_REFCNT ; 
 int /*<<< orphan*/  EBUSY ; 
 struct bpf_prog* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 

struct bpf_prog *bpf_prog_add(struct bpf_prog *prog, int i)
{
	if (atomic_add_return(i, &prog->aux->refcnt) > BPF_MAX_REFCNT) {
		atomic_sub(i, &prog->aux->refcnt);
		return ERR_PTR(-EBUSY);
	}
	return prog;
}