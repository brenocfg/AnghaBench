#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  regno; } ;
struct TYPE_8__ {TYPE_2__ offset; } ;
struct TYPE_6__ {int kind; } ;
struct TYPE_9__ {TYPE_3__ addr; TYPE_1__ shifter; } ;
typedef  TYPE_4__ aarch64_opnd_info ;

/* Variables and functions */
#define  AARCH64_MOD_LSL 131 
#define  AARCH64_MOD_SXTW 130 
#define  AARCH64_MOD_SXTX 129 
#define  AARCH64_MOD_UXTW 128 
 int /*<<< orphan*/  AARCH64_OPND_QLF_W ; 
 int /*<<< orphan*/  AARCH64_OPND_QLF_X ; 
 int /*<<< orphan*/  abort () ; 
 char const* get_int_reg_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *
get_offset_int_reg_name (const aarch64_opnd_info *opnd)
{
  switch (opnd->shifter.kind)
    {
    case AARCH64_MOD_UXTW:
    case AARCH64_MOD_SXTW:
      return get_int_reg_name (opnd->addr.offset.regno, AARCH64_OPND_QLF_W, 0);

    case AARCH64_MOD_LSL:
    case AARCH64_MOD_SXTX:
      return get_int_reg_name (opnd->addr.offset.regno, AARCH64_OPND_QLF_X, 0);

    default:
      abort ();
    }
}