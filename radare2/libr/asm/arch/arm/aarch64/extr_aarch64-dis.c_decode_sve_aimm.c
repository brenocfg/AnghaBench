#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {int value; } ;
struct TYPE_6__ {int amount; int operator_present; int amount_present; int /*<<< orphan*/  kind; } ;
struct TYPE_7__ {TYPE_1__ imm; TYPE_2__ shifter; } ;
typedef  TYPE_3__ aarch64_opnd_info ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_MOD_LSL ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bfd_boolean
decode_sve_aimm (aarch64_opnd_info *info, int64_t value)
{
  info->shifter.kind = AARCH64_MOD_LSL;
  info->shifter.amount = 0;
  if (info->imm.value & 0x100)
    {
      if (value == 0)
	/* Decode 0x100 as #0, LSL #8.  */
	info->shifter.amount = 8;
      else
	value *= 256;
    }
  info->shifter.operator_present = (info->shifter.amount != 0);
  info->shifter.amount_present = (info->shifter.amount != 0);
  info->imm.value = value;
  return TRUE;
}