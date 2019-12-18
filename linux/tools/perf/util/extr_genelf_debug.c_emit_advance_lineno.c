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
 int /*<<< orphan*/  DW_LNS_advance_line ; 
 int /*<<< orphan*/  emit_opcode_signed (struct buffer_ext*,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static void emit_advance_lineno(struct buffer_ext  *be, long delta_lineno)
{
	emit_opcode_signed(be, DW_LNS_advance_line, delta_lineno);
}