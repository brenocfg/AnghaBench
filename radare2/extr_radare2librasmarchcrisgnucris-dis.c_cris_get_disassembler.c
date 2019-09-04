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
typedef  int /*<<< orphan*/  disassembler_ftype ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  print_insn_crisv32_without_register_prefix ; 

disassembler_ftype
cris_get_disassembler (bfd *abfd)
{
#if CR16_SUPPORTS_CPU
const int mode = 0; // V32 by default
  /* If there's no bfd in sight, we return what is valid as input in all
     contexts if fed back to the assembler: disassembly *with* register
     prefix.  Unfortunately this will be totally wrong for v32.  */
if (!abfd) {
	return print_insn_cris_with_register_prefix;
}

if (bfd_get_symbol_leading_char (abfd) == 0) {
	switch (mode) {
	case 0: // V32
		return print_insn_crisv32_with_register_prefix;
	case 1: // V10_V32
		return print_insn_crisv10_v32_with_register_prefix;
	default:

		/* We default to v10.  This may be specifically specified in the
	 bfd mach, but is also the default setting.  */
		return print_insn_cris_with_register_prefix;
	}
    }

switch (mode) {
case 0: // V32
  //if (bfd_get_mach (abfd) == bfd_mach_cris_v32)
    return print_insn_crisv32_without_register_prefix;
case 1: // V10_V32
  //if (bfd_get_mach (abfd) == bfd_mach_cris_v10_v32)
    return print_insn_crisv10_v32_without_register_prefix;
default:
  return print_insn_cris_without_register_prefix;
}
#else
	return print_insn_crisv32_without_register_prefix;
#endif
}