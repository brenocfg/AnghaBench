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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void
print_ppc_disassembler_options (FILE *stream)
{
  fprintf (stream, "\n\
The following PPC specific disassembler options are supported for use with\n\
the -M switch:\n");

  fprintf (stream, "  booke|booke32|booke64    Disassemble the BookE instructions\n");
  fprintf (stream, "  e300                     Disassemble the e300 instructions\n");
  fprintf (stream, "  e500|e500x2              Disassemble the e500 instructions\n");
  fprintf (stream, "  e500mc                   Disassemble the e500mc instructions\n");
  fprintf (stream, "  440                      Disassemble the 440 instructions\n");
  fprintf (stream, "  464                      Disassemble the 464 instructions\n");
  fprintf (stream, "  efs                      Disassemble the EFS instructions\n");
  fprintf (stream, "  ppcps                    Disassemble the PowerPC paired singles instructions\n");
  fprintf (stream, "  power4                   Disassemble the Power4 instructions\n");
  fprintf (stream, "  power5                   Disassemble the Power5 instructions\n");
  fprintf (stream, "  power6                   Disassemble the Power6 instructions\n");
  fprintf (stream, "  power7                   Disassemble the Power7 instructions\n");
  fprintf (stream, "  vsx                      Disassemble the Vector-Scalar (VSX) instructions\n");
  fprintf (stream, "  32                       Do not disassemble 64-bit instructions\n");
  fprintf (stream, "  64                       Allow disassembly of 64-bit instructions\n");
}