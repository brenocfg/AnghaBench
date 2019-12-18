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
 int /*<<< orphan*/  bpf_raw_tp_nest_level ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_bpf_raw_tp_regs(void)
{
	this_cpu_dec(bpf_raw_tp_nest_level);
}