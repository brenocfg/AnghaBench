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
struct bpf_program {int idx; scalar_t__ insns_cnt; scalar_t__ nr_reloc; int /*<<< orphan*/  reloc_desc; int /*<<< orphan*/  insns; int /*<<< orphan*/  pin_name; int /*<<< orphan*/  section_name; int /*<<< orphan*/  name; int /*<<< orphan*/  (* clear_priv ) (struct bpf_program*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_program__unload (struct bpf_program*) ; 
 int /*<<< orphan*/  stub1 (struct bpf_program*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bpf_program__exit(struct bpf_program *prog)
{
	if (!prog)
		return;

	if (prog->clear_priv)
		prog->clear_priv(prog, prog->priv);

	prog->priv = NULL;
	prog->clear_priv = NULL;

	bpf_program__unload(prog);
	zfree(&prog->name);
	zfree(&prog->section_name);
	zfree(&prog->pin_name);
	zfree(&prog->insns);
	zfree(&prog->reloc_desc);

	prog->nr_reloc = 0;
	prog->insns_cnt = 0;
	prog->idx = -1;
}