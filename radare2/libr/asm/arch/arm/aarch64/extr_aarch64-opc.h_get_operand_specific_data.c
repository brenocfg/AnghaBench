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
struct TYPE_3__ {unsigned int flags; } ;
typedef  TYPE_1__ aarch64_operand ;

/* Variables and functions */
 unsigned int OPD_F_OD_LSB ; 
 unsigned int OPD_F_OD_MASK ; 

__attribute__((used)) static inline unsigned int
get_operand_specific_data (const aarch64_operand *operand)
{
  return (operand->flags & OPD_F_OD_MASK) >> OPD_F_OD_LSB;
}