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
struct disassemble_info {int /*<<< orphan*/ * private_data; } ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 int /*<<< orphan*/  POWERPC_DIALECT (struct disassemble_info*) ; 
 int /*<<< orphan*/  powerpc_init_dialect (struct disassemble_info*) ; 
 int print_insn_powerpc (int /*<<< orphan*/ ,struct disassemble_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
print_insn_little_powerpc (bfd_vma memaddr, struct disassemble_info *info)
{
	if (info->private_data == NULL && !powerpc_init_dialect (info)) {
		return -1;
	}
	return print_insn_powerpc (memaddr, info, 0, POWERPC_DIALECT (info));
}