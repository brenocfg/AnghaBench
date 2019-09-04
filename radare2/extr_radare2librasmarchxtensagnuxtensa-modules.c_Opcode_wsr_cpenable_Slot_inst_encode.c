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
typedef  int* xtensa_insnbuf ;

/* Variables and functions */

__attribute__((used)) static void
Opcode_wsr_cpenable_Slot_inst_encode (xtensa_insnbuf slotbuf)
{
  slotbuf[0] = 0x13e000;
}