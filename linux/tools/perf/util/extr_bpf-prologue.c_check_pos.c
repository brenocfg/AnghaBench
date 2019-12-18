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
struct bpf_insn_pos {scalar_t__ pos; scalar_t__ end; } ;

/* Variables and functions */
 int BPF_LOADER_ERRNO__PROLOGUE2BIG ; 

__attribute__((used)) static int
check_pos(struct bpf_insn_pos *pos)
{
	if (!pos->pos || pos->pos >= pos->end)
		return -BPF_LOADER_ERRNO__PROLOGUE2BIG;
	return 0;
}