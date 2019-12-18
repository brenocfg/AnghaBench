#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * qualifiers_list; } ;
typedef  TYPE_1__ aarch64_opcode ;

/* Variables and functions */
 size_t get_data_pattern (int /*<<< orphan*/ ) ; 
 int* significant_operand_index ; 

int
aarch64_select_operand_for_sizeq_field_coding (const aarch64_opcode *opcode)
{
  return
    significant_operand_index [get_data_pattern (opcode->qualifiers_list[0])];
}