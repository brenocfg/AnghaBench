#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int flags; scalar_t__ value; } ;
typedef  TYPE_1__ aarch64_sys_ins_reg ;
typedef  int /*<<< orphan*/  aarch64_feature_set ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_CPU_HAS_FEATURE (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AARCH64_FEATURE_V8_2 ; 
 int /*<<< orphan*/  C12 ; 
 int /*<<< orphan*/  C7 ; 
 int /*<<< orphan*/  C9 ; 
 scalar_t__ CPENS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int F_ARCHEXT ; 
 int /*<<< orphan*/  TRUE ; 

extern bfd_boolean
aarch64_sys_ins_reg_supported_p (const aarch64_feature_set features,
				 const aarch64_sys_ins_reg *reg)
{
  if (!(reg->flags & F_ARCHEXT))
    return TRUE;

  /* DC CVAP.  Values are from aarch64_sys_regs_dc.  */
  if (reg->value == CPENS (3, C7, C12, 1)
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_2))
    return FALSE;

  /* AT S1E1RP, AT S1E1WP.  Values are from aarch64_sys_regs_at.  */
  if ((reg->value == CPENS (0, C7, C9, 0)
       || reg->value == CPENS (0, C7, C9, 1))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_2))
    return FALSE;

  return TRUE;
}