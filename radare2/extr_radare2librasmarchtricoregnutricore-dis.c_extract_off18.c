#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long opcode; } ;

/* Variables and functions */
 TYPE_1__ dec_insn ; 

__attribute__((used)) static unsigned long
extract_off18 ()
{
  unsigned long o1, o2, o3, o4;
  unsigned long val = dec_insn.opcode;

  o1 = (val & 0x003f0000) >> 16;
  o2 = (val & 0xf0000000) >> 22;
  o3 = (val & 0x03c00000) >> 12;
  o4 = (val & 0x0000f000) << 2;
  return o1 | o2 | o3 | o4;
}