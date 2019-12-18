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

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_SCHED_CLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_load_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prog ; 

__attribute__((used)) static int bpf_try_load_prog(int insns, int fd_map,
			     void (*bpf_filler)(unsigned int insns,
						int fd_map))
{
	int fd_prog;

	bpf_filler(insns, fd_map);
	fd_prog = bpf_load_program(BPF_PROG_TYPE_SCHED_CLS, prog, insns, "", 0,
				   NULL, 0);
	assert(fd_prog > 0);
	if (fd_map > 0)
		bpf_filler(insns, 0);
	return fd_prog;
}