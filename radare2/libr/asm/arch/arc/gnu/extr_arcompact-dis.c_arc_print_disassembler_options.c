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
arc_print_disassembler_options (FILE *stream)
{
  fprintf (stream, "\n\
 ARC-specific disassembler options:\n\
 use with the -M switch, with options separated by commas\n\n");

  fprintf (stream, "  insn-stream    Show the instruction byte stream from most\n");
  fprintf (stream, "                 significant byte to least significant byte (excluding LIMM).\n");
  fprintf (stream, "                 This option is useful for viewing the actual encoding of instructions.\n");
  
  fprintf (stream, "  simd           Enable SIMD instructions disassembly.\n\n");
}