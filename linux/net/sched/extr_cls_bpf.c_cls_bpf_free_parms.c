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
struct cls_bpf_prog {int /*<<< orphan*/  bpf_ops; int /*<<< orphan*/  bpf_name; int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_put (int /*<<< orphan*/ ) ; 
 scalar_t__ cls_bpf_is_ebpf (struct cls_bpf_prog*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cls_bpf_free_parms(struct cls_bpf_prog *prog)
{
	if (cls_bpf_is_ebpf(prog))
		bpf_prog_put(prog->filter);
	else
		bpf_prog_destroy(prog->filter);

	kfree(prog->bpf_name);
	kfree(prog->bpf_ops);
}