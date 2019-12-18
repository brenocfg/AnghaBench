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
struct TYPE_2__ {int /*<<< orphan*/  rcu; int /*<<< orphan*/  btf; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bpf_prog_put_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_prog_free_linfo (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_kallsyms_del_all (struct bpf_prog*) ; 
 int /*<<< orphan*/  btf_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 

__attribute__((used)) static void __bpf_prog_put_noref(struct bpf_prog *prog, bool deferred)
{
	bpf_prog_kallsyms_del_all(prog);
	btf_put(prog->aux->btf);
	bpf_prog_free_linfo(prog);

	if (deferred)
		call_rcu(&prog->aux->rcu, __bpf_prog_put_rcu);
	else
		__bpf_prog_put_rcu(&prog->aux->rcu);
}