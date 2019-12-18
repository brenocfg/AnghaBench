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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ aarch64_operand ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int OPD_F_SHIFT_BY_2 ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline bfd_boolean
operand_need_shift_by_two (const aarch64_operand *operand)
{
  return (operand->flags & OPD_F_SHIFT_BY_2) ? TRUE : FALSE;
}