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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_override_return (struct pt_regs*,unsigned long) ; 

int bpf_prog1(struct pt_regs *ctx)
{
	unsigned long rc = -12;

	bpf_override_return(ctx, rc);
	return 0;
}