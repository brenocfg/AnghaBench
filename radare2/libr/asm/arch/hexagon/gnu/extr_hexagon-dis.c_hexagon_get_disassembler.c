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
 unsigned long bfd_big_endian (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hexagon_get_disassembler_from_mach (unsigned long,unsigned long) ; 

disassembler_ftype
hexagon_get_disassembler(
    bfd *abfd
)
{
  unsigned long machine = 0; // XXX bfd_get_mach(abfd);
  unsigned long big_p = bfd_big_endian(abfd);
  return (hexagon_get_disassembler_from_mach(machine, big_p));
}