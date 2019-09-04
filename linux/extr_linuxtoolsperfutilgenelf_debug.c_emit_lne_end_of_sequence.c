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
 int /*<<< orphan*/  DW_LNE_end_sequence ; 
 int /*<<< orphan*/  emit_extended_opcode (struct buffer_ext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_lne_end_of_sequence(struct buffer_ext *be)
{
	emit_extended_opcode(be, DW_LNE_end_sequence, NULL, 0);
}