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
struct bpf_regs {int Rs; scalar_t__ R; } ;

/* Variables and functions */

__attribute__((used)) static void set_return(struct bpf_regs *r)
{
	r->R = 0;
	r->Rs = true;
}