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
struct TYPE_3__ {int flags; int value; } ;
typedef  TYPE_1__ aarch64_sys_reg ;
typedef  int /*<<< orphan*/  aarch64_feature_set ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_CPU_HAS_FEATURE (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AARCH64_FEATURE_PAN ; 
 int /*<<< orphan*/  AARCH64_FEATURE_V8_2 ; 
 int /*<<< orphan*/  AARCH64_FEATURE_V8_4 ; 
 int /*<<< orphan*/  FALSE ; 
 int F_ARCHEXT ; 
 int /*<<< orphan*/  TRUE ; 

bfd_boolean
aarch64_pstatefield_supported_p (const aarch64_feature_set features,
				 const aarch64_sys_reg *reg)
{
  if (!(reg->flags & F_ARCHEXT))
    return TRUE;

  /* PAN.  Values are from aarch64_pstatefields.  */
  if (reg->value == 0x04
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_PAN))
    return FALSE;

  /* UAO.  Values are from aarch64_pstatefields.  */
  if (reg->value == 0x03
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_2))
    return FALSE;

  /* DIT.  Values are from aarch64_pstatefields.  */
  if (reg->value == 0x1a
      && !AARCH64_CPU_HAS_FEATURE (features, AARCH64_FEATURE_V8_4))
    return FALSE;

  return TRUE;
}