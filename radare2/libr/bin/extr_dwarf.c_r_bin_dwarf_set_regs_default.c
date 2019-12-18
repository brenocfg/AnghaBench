#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  default_is_stmt; } ;
struct TYPE_5__ {int file; int line; void* end_sequence; void* basic_block; int /*<<< orphan*/  is_stmt; scalar_t__ column; scalar_t__ address; } ;
typedef  TYPE_1__ RBinDwarfSMRegisters ;
typedef  TYPE_2__ RBinDwarfLNPHeader ;

/* Variables and functions */
 void* DWARF_FALSE ; 

__attribute__((used)) static void r_bin_dwarf_set_regs_default(const RBinDwarfLNPHeader *hdr, RBinDwarfSMRegisters *regs) {
	regs->address = 0;
	regs->file = 1;
	regs->line = 1;
	regs->column = 0;
	regs->is_stmt = hdr->default_is_stmt;
	regs->basic_block = DWARF_FALSE;
	regs->end_sequence = DWARF_FALSE;
}