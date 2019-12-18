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
struct bpf_prog_linfo {struct bpf_prog_linfo* jited_linfo_func_idx; struct bpf_prog_linfo* nr_jited_linfo_per_func; struct bpf_prog_linfo* raw_jited_linfo; struct bpf_prog_linfo* raw_linfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct bpf_prog_linfo*) ; 

void bpf_prog_linfo__free(struct bpf_prog_linfo *prog_linfo)
{
	if (!prog_linfo)
		return;

	free(prog_linfo->raw_linfo);
	free(prog_linfo->raw_jited_linfo);
	free(prog_linfo->nr_jited_linfo_per_func);
	free(prog_linfo->jited_linfo_func_idx);
	free(prog_linfo);
}