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
struct bpf_program {int dummy; } ;

/* Variables and functions */
 int bpf_program__nth_fd (struct bpf_program const*,int /*<<< orphan*/ ) ; 

int bpf_program__fd(const struct bpf_program *prog)
{
	return bpf_program__nth_fd(prog, 0);
}