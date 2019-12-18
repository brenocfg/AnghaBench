#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct disassemble_info {scalar_t__ flavour; int /*<<< orphan*/  endian_code; TYPE_1__* section; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_4__ {int e_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ENDIAN_LITTLE ; 
 int EF_ARM_BE8 ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_2__* elf_elfheader (int /*<<< orphan*/ ) ; 
 int print_insn (int /*<<< orphan*/ ,struct disassemble_info*,int /*<<< orphan*/ ) ; 

int
print_insn_big_arm (bfd_vma pc, struct disassemble_info *info)
{
  /* Detect BE8-ness and record it in the disassembler info.  */
#if 0
  if (info->flavour == bfd_target_elf_flavour
      && info->section != NULL
      && (elf_elfheader (info->section->owner)->e_flags & EF_ARM_BE8))
    info->endian_code = BFD_ENDIAN_LITTLE;
#endif

  return print_insn (pc, info, FALSE);
}