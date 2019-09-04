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
struct bpf_program {int /*<<< orphan*/  prog_ifindex; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */

void bpf_program__set_ifindex(struct bpf_program *prog, __u32 ifindex)
{
	prog->prog_ifindex = ifindex;
}