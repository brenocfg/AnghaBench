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
typedef  TYPE_1__ aarch64_sys_reg ;
typedef  int /*<<< orphan*/  aarch64_feature_set ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_CPU_HAS_FEATURE (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AARCH64_FEATURE_PAN ; 
 int /*<<< orphan*/  AARCH64_FEATURE_PROFILE ; 
 int /*<<< orphan*/  AARCH64_FEATURE_RAS ; 
 int /*<<< orphan*/  AARCH64_FEATURE_SVE ; 
 int /*<<< orphan*/  AARCH64_FEATURE_V8_1 ; 
 int /*<<< orphan*/  AARCH64_FEATURE_V8_2 ; 
 int /*<<< orphan*/  AARCH64_FEATURE_V8_3 ; 
 int /*<<< orphan*/  AARCH64_FEATURE_V8_4 ; 
 int /*<<< orphan*/  C0 ; 
 int /*<<< orphan*/  C1 ; 
 int /*<<< orphan*/  C10 ; 
 int /*<<< orphan*/  C12 ; 
 int /*<<< orphan*/  C13 ; 
 int /*<<< orphan*/  C14 ; 
 int /*<<< orphan*/  C2 ; 
 int /*<<< orphan*/  C3 ; 
 int /*<<< orphan*/  C4 ; 
 int /*<<< orphan*/  C5 ; 
 int /*<<< orphan*/  C6 ; 
 int /*<<< orphan*/  C7 ; 
 int /*<<< orphan*/  C8 ; 
 int /*<<< orphan*/  C9 ; 
 scalar_t__ CPENC (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CPENS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CPEN_ (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int F_ARCHEXT ; 
 int /*<<< orphan*/  TRUE ; 

bfd_boolean
aarch64_sys_reg_supported_p (const aarch64_feature_set features,
			     const aarch64_sys_reg *reg)
{
  if (!(reg->flags & F_ARCHEXT))
    return TRUE;

  /* PAN.  Values are from aarch64_sys_regs.  */
  if (reg->value == CPEN_(0,C2,3)
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_PAN))
    return FALSE;

  /* Virtualization host extensions: system registers.  */
  if ((reg->value == CPENC (3, 4, C2, C0, 1)
       || reg->value == CPENC (3, 4, C13, C0, 1)
       || reg->value == CPENC (3, 4, C14, C3, 0)
       || reg->value == CPENC (3, 4, C14, C3, 1)
       || reg->value == CPENC (3, 4, C14, C3, 2))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_1))
      return FALSE;

  /* Virtualization host extensions: *_el12 names of *_el1 registers.  */
  if ((reg->value == CPEN_ (5, C0, 0)
       || reg->value == CPEN_ (5, C0, 1)
       || reg->value == CPENC (3, 5, C1, C0, 0)
       || reg->value == CPENC (3, 5, C1, C0, 2)
       || reg->value == CPENC (3, 5, C2, C0, 0)
       || reg->value == CPENC (3, 5, C2, C0, 1)
       || reg->value == CPENC (3, 5, C2, C0, 2)
       || reg->value == CPENC (3, 5, C5, C1, 0)
       || reg->value == CPENC (3, 5, C5, C1, 1)
       || reg->value == CPENC (3, 5, C5, C2, 0)
       || reg->value == CPENC (3, 5, C6, C0, 0)
       || reg->value == CPENC (3, 5, C10, C2, 0)
       || reg->value == CPENC (3, 5, C10, C3, 0)
       || reg->value == CPENC (3, 5, C12, C0, 0)
       || reg->value == CPENC (3, 5, C13, C0, 1)
       || reg->value == CPENC (3, 5, C14, C1, 0))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_1))
    return FALSE;

  /* Virtualization host extensions: *_el02 names of *_el0 registers.  */
  if ((reg->value == CPENC (3, 5, C14, C2, 0)
       || reg->value == CPENC (3, 5, C14, C2, 1)
       || reg->value == CPENC (3, 5, C14, C2, 2)
       || reg->value == CPENC (3, 5, C14, C3, 0)
       || reg->value == CPENC (3, 5, C14, C3, 1)
       || reg->value == CPENC (3, 5, C14, C3, 2))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_1))
    return FALSE;

  /* ARMv8.2 features.  */

  /* ID_AA64MMFR2_EL1.  */
  if (reg->value == CPENC (3, 0, C0, C7, 2)
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_2))
    return FALSE;

  /* PSTATE.UAO.  */
  if (reg->value == CPEN_ (0, C2, 4)
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_2))
    return FALSE;

  /* RAS extension.  */

  /* ERRIDR_EL1, ERRSELR_EL1, ERXFR_EL1, ERXCTLR_EL1, ERXSTATUS_EL, ERXADDR_EL1,
     ERXMISC0_EL1 AND ERXMISC1_EL1.  */
  if ((reg->value == CPENC (3, 0, C5, C3, 0)
       || reg->value == CPENC (3, 0, C5, C3, 1)
       || reg->value == CPENC (3, 0, C5, C3, 2)
       || reg->value == CPENC (3, 0, C5, C3, 3)
       || reg->value == CPENC (3, 0, C5, C4, 0)
       || reg->value == CPENC (3, 0, C5, C4, 1)
       || reg->value == CPENC (3, 0, C5, C4, 2)
       || reg->value == CPENC (3, 0, C5, C4, 3)
       || reg->value == CPENC (3, 0, C5, C5, 0)
       || reg->value == CPENC (3, 0, C5, C5, 1))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_RAS))
    return FALSE;

  /* VSESR_EL2, DISR_EL1 and VDISR_EL2.  */
  if ((reg->value == CPENC (3, 4, C5, C2, 3)
       || reg->value == CPENC (3, 0, C12, C1, 1)
       || reg->value == CPENC (3, 4, C12, C1, 1))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_RAS))
    return FALSE;

  /* Statistical Profiling extension.  */
  if ((reg->value == CPENC (3, 0, C9, C10, 0)
       || reg->value == CPENC (3, 0, C9, C10, 1)
       || reg->value == CPENC (3, 0, C9, C10, 3)
       || reg->value == CPENC (3, 0, C9, C10, 7)
       || reg->value == CPENC (3, 0, C9, C9, 0)
       || reg->value == CPENC (3, 0, C9, C9, 2)
       || reg->value == CPENC (3, 0, C9, C9, 3)
       || reg->value == CPENC (3, 0, C9, C9, 4)
       || reg->value == CPENC (3, 0, C9, C9, 5)
       || reg->value == CPENC (3, 0, C9, C9, 6)
       || reg->value == CPENC (3, 0, C9, C9, 7)
       || reg->value == CPENC (3, 4, C9, C9, 0)
       || reg->value == CPENC (3, 5, C9, C9, 0))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_PROFILE))
    return FALSE;

  /* ARMv8.3 Pointer authentication keys.  */
  if ((reg->value == CPENC (3, 0, C2, C1, 0)
       || reg->value == CPENC (3, 0, C2, C1, 1)
       || reg->value == CPENC (3, 0, C2, C1, 2)
       || reg->value == CPENC (3, 0, C2, C1, 3)
       || reg->value == CPENC (3, 0, C2, C2, 0)
       || reg->value == CPENC (3, 0, C2, C2, 1)
       || reg->value == CPENC (3, 0, C2, C2, 2)
       || reg->value == CPENC (3, 0, C2, C2, 3)
       || reg->value == CPENC (3, 0, C2, C3, 0)
       || reg->value == CPENC (3, 0, C2, C3, 1))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_3))
    return FALSE;

  /* SVE.  */
  if ((reg->value == CPENC (3, 0, C0, C4, 4)
       || reg->value == CPENC (3, 0, C1, C2, 0)
       || reg->value == CPENC (3, 4, C1, C2, 0)
       || reg->value == CPENC (3, 6, C1, C2, 0)
       || reg->value == CPENC (3, 5, C1, C2, 0)
       || reg->value == CPENC (3, 0, C0, C0, 7))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_SVE))
    return FALSE;

  /* ARMv8.4 features.  */

  /* PSTATE.DIT.  */
  if (reg->value == CPEN_ (3, C2, 5)
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_4))
    return FALSE;

  /* Virtualization extensions.  */
  if ((reg->value == CPENC(3, 4, C2, C6, 2)
       || reg->value == CPENC(3, 4, C2, C6, 0)
       || reg->value == CPENC(3, 4, C14, C4, 0)
       || reg->value == CPENC(3, 4, C14, C4, 2)
       || reg->value == CPENC(3, 4, C14, C4, 1)
       || reg->value == CPENC(3, 4, C14, C5, 0)
       || reg->value == CPENC(3, 4, C14, C5, 2)
       || reg->value == CPENC(3, 4, C14, C5, 1)
       || reg->value == CPENC(3, 4, C1, C3, 1)
       || reg->value == CPENC(3, 4, C2, C2, 0))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_4))
    return FALSE;

  /* ARMv8.4 TLB instructions.  */
  if ((reg->value == CPENS (0, C8, C1, 0)
       || reg->value == CPENS (0, C8, C1, 1)
       || reg->value == CPENS (0, C8, C1, 2)
       || reg->value == CPENS (0, C8, C1, 3)
       || reg->value == CPENS (0, C8, C1, 5)
       || reg->value == CPENS (0, C8, C1, 7)
       || reg->value == CPENS (4, C8, C4, 0)
       || reg->value == CPENS (4, C8, C4, 4)
       || reg->value == CPENS (4, C8, C1, 1)
       || reg->value == CPENS (4, C8, C1, 5)
       || reg->value == CPENS (4, C8, C1, 6)
       || reg->value == CPENS (6, C8, C1, 1)
       || reg->value == CPENS (6, C8, C1, 5)
       || reg->value == CPENS (4, C8, C1, 0)
       || reg->value == CPENS (4, C8, C1, 4)
       || reg->value == CPENS (6, C8, C1, 0)
       || reg->value == CPENS (0, C8, C6, 1)
       || reg->value == CPENS (0, C8, C6, 3)
       || reg->value == CPENS (0, C8, C6, 5)
       || reg->value == CPENS (0, C8, C6, 7)
       || reg->value == CPENS (0, C8, C2, 1)
       || reg->value == CPENS (0, C8, C2, 3)
       || reg->value == CPENS (0, C8, C2, 5)
       || reg->value == CPENS (0, C8, C2, 7)
       || reg->value == CPENS (0, C8, C5, 1)
       || reg->value == CPENS (0, C8, C5, 3)
       || reg->value == CPENS (0, C8, C5, 5)
       || reg->value == CPENS (0, C8, C5, 7)
       || reg->value == CPENS (4, C8, C0, 2)
       || reg->value == CPENS (4, C8, C0, 6)
       || reg->value == CPENS (4, C8, C4, 2)
       || reg->value == CPENS (4, C8, C4, 6)
       || reg->value == CPENS (4, C8, C4, 3)
       || reg->value == CPENS (4, C8, C4, 7)
       || reg->value == CPENS (4, C8, C6, 1)
       || reg->value == CPENS (4, C8, C6, 5)
       || reg->value == CPENS (4, C8, C2, 1)
       || reg->value == CPENS (4, C8, C2, 5)
       || reg->value == CPENS (4, C8, C5, 1)
       || reg->value == CPENS (4, C8, C5, 5)
       || reg->value == CPENS (6, C8, C6, 1)
       || reg->value == CPENS (6, C8, C6, 5)
       || reg->value == CPENS (6, C8, C2, 1)
       || reg->value == CPENS (6, C8, C2, 5)
       || reg->value == CPENS (6, C8, C5, 1)
       || reg->value == CPENS (6, C8, C5, 5))
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_4))
    return FALSE;

  return TRUE;
}