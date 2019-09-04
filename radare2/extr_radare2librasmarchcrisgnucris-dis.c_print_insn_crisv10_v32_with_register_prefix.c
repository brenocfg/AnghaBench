#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  private_data; } ;
typedef  TYPE_1__ disassemble_info ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cris_dis_common_v10_v32 ; 
 int /*<<< orphan*/  cris_parse_disassembler_options (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int print_insn_cris_generic (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
print_insn_crisv10_v32_with_register_prefix (bfd_vma vma,
					     disassemble_info *info)
{
	if (!info->private_data && !cris_parse_disassembler_options (info, cris_dis_common_v10_v32)) {
		return -1;
	}
	return print_insn_cris_generic (vma, info, TRUE);
}