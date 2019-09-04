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
struct buffer_ext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_LNS_advance_pc ; 
 int /*<<< orphan*/  emit_opcode_unsigned (struct buffer_ext*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void emit_advance_pc(struct buffer_ext *be, unsigned long delta_pc)
{
	emit_opcode_unsigned(be, DW_LNS_advance_pc, delta_pc);
}