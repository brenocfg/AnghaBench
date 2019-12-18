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
struct cris_disasm_data {scalar_t__ distype; } ;

/* Variables and functions */
 scalar_t__ cris_dis_v32 ; 

__attribute__((used)) static char *
print_flags (struct cris_disasm_data *disdata, unsigned int insn, char *cp)
{
  /* Use the v8 (Etrax 100) flag definitions for disassembly.
     The differences with v0 (Etrax 1..4) vs. Svinto are:
      v0 'd' <=> v8 'm'
      v0 'e' <=> v8 'b'.
     FIXME: Emit v0..v3 flag names somehow.  */
  static const char v8_fnames[] = "cvznxibm";
  static const char v32_fnames[] = "cvznxiup";
  const char *fnames
    = disdata->distype == cris_dis_v32 ? v32_fnames : v8_fnames;

  unsigned char flagbits = (((insn >> 8) & 0xf0) | (insn & 15));
  int i;

  for (i = 0; i < 8; i++) {
	  if (flagbits & (1 << i)) {
		  *cp++ = fnames[i];
	  }
  }

  return cp;
}