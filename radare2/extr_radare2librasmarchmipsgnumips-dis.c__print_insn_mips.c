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
struct disassemble_info {int (* read_memory_func ) (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ;int /*<<< orphan*/  (* memory_error_func ) (int,int,struct disassemble_info*) ;int /*<<< orphan*/  disassembler_options; } ;
typedef  enum bfd_endian { ____Placeholder_bfd_endian } bfd_endian ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int BFD_ENDIAN_BIG ; 
 int INSNLEN ; 
 scalar_t__ bfd_getb32 (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_getl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_mips_dis_options (int /*<<< orphan*/ ) ; 
 int print_insn_mips (int,unsigned long,struct disassemble_info*) ; 
 int print_insn_mips16 (int,struct disassemble_info*) ; 
 int /*<<< orphan*/  set_default_mips_dis_options (struct disassemble_info*) ; 
 int stub1 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int /*<<< orphan*/  stub2 (int,int,struct disassemble_info*) ; 

__attribute__((used)) static int
_print_insn_mips (bfd_vma memaddr,
		  struct disassemble_info *info,
		  enum bfd_endian endianness)
{
  bfd_byte buffer[INSNLEN];
  int status;

  set_default_mips_dis_options (info);
  parse_mips_dis_options (info->disassembler_options);

#if 1
  /* FIXME: If odd address, this is CLEARLY a mips 16 instruction.  */
  /* Only a few tools will work this way.  */
  if (memaddr & 0x01) {
	  return print_insn_mips16 (memaddr, info);
  }
#endif

#if SYMTAB_AVAILABLE
  if (info->mach == bfd_mach_mips16 || (info->flavour == bfd_target_elf_flavour && info->symbols != NULL && ((*(elf_symbol_type **)info->symbols)->internal_elf_sym.st_other == STO_MIPS16))) {
	  return print_insn_mips16 (memaddr, info);
  }
#endif

  status = (*info->read_memory_func) (memaddr, buffer, INSNLEN, info);
  if (status == 0)
    {
      unsigned long insn;

      if (endianness == BFD_ENDIAN_BIG) {
	      insn = (unsigned long)bfd_getb32 (buffer);
      } else {
	      insn = (unsigned long)bfd_getl32 (buffer);
      }

      return print_insn_mips (memaddr, insn, info);
    }
  else
    {
      (*info->memory_error_func) (status, memaddr, info);
      return -1;
    }
}