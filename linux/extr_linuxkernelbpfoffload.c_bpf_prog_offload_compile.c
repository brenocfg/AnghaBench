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
struct bpf_prog {int /*<<< orphan*/  bpf_func; } ;

/* Variables and functions */
 int bpf_prog_offload_translate (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_warn_on_exec ; 

int bpf_prog_offload_compile(struct bpf_prog *prog)
{
	prog->bpf_func = bpf_prog_warn_on_exec;

	return bpf_prog_offload_translate(prog);
}