#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long ubyte ;
struct debug_entry {unsigned int lineno; unsigned long addr; } ;
struct TYPE_2__ {unsigned int line_base; unsigned int line_range; unsigned long minimum_instruction_length; unsigned int opcode_base; } ;

/* Variables and functions */
 TYPE_1__ default_debug_line_header ; 

__attribute__((used)) static ubyte get_special_opcode(struct debug_entry *ent,
				unsigned int last_line,
				unsigned long last_vma)
{
	unsigned int temp;
	unsigned long delta_addr;

	/*
	 * delta from line_base
	 */
	temp = (ent->lineno - last_line) - default_debug_line_header.line_base;

	if (temp >= default_debug_line_header.line_range)
		return 0;

	/*
	 * delta of addresses
	 */
	delta_addr = (ent->addr - last_vma) / default_debug_line_header.minimum_instruction_length;

	/* This is not sufficient to ensure opcode will be in [0-256] but
	 * sufficient to ensure when summing with the delta lineno we will
	 * not overflow the unsigned long opcode */

	if (delta_addr <= 256 / default_debug_line_header.line_range) {
		unsigned long opcode = temp +
			(delta_addr * default_debug_line_header.line_range) +
			default_debug_line_header.opcode_base;

		return opcode <= 255 ? opcode : 0;
	}
	return 0;
}