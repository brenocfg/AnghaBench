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
struct cls_bpf_prog {int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int /*<<< orphan*/  cls_bpf_free_parms (struct cls_bpf_prog*) ; 
 int /*<<< orphan*/  kfree (struct cls_bpf_prog*) ; 
 int /*<<< orphan*/  tcf_exts_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_put_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cls_bpf_delete_prog(struct cls_bpf_prog *prog)
{
	tcf_exts_destroy(&prog->exts);
	tcf_exts_put_net(&prog->exts);

	cls_bpf_free_parms(prog);
	kfree(prog);
}