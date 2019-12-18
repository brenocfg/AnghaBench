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
typedef  int arc_insn ;

/* Variables and functions */

int
ac_lpcc_insn(arc_insn insn)
{
    return ( ((insn & 0xfffff000) == 0x20a80000) ||
	     ((insn & 0xfffff020) == 0x20a80020));
}