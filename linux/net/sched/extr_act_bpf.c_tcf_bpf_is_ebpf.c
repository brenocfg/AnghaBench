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
struct tcf_bpf {int /*<<< orphan*/  bpf_ops; } ;

/* Variables and functions */

__attribute__((used)) static bool tcf_bpf_is_ebpf(const struct tcf_bpf *prog)
{
	return !prog->bpf_ops;
}