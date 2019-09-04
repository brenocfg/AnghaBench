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
typedef  int /*<<< orphan*/  u_char ;
struct sym_hcb {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void sym_init_tcb (struct sym_hcb *np, u_char tn)
{
#if 0	/*  Hmmm... this checking looks paranoid. */
	/*
	 *  Check some alignments required by the chip.
	 */	
	assert (((offsetof(struct sym_reg, nc_sxfer) ^
		offsetof(struct sym_tcb, head.sval)) &3) == 0);
	assert (((offsetof(struct sym_reg, nc_scntl3) ^
		offsetof(struct sym_tcb, head.wval)) &3) == 0);
#endif
}