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

/* Variables and functions */
 int /*<<< orphan*/  hexagon_decode_inst ; 
 int /*<<< orphan*/  hexagon_get_opcode_mach (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  hexagon_opcode_init_tables (int /*<<< orphan*/ ) ; 

disassembler_ftype
hexagon_get_disassembler_from_mach(
  unsigned long machine,
  unsigned long big_p
)
{
  hexagon_opcode_init_tables(hexagon_get_opcode_mach(machine, big_p));
  return hexagon_decode_inst;
}