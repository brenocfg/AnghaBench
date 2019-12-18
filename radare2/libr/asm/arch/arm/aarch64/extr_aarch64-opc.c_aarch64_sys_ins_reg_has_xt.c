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
typedef  int bfd_boolean ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ aarch64_sys_ins_reg ;

/* Variables and functions */
 int F_HASXT ; 

bfd_boolean
aarch64_sys_ins_reg_has_xt (const aarch64_sys_ins_reg *sys_ins_reg)
{
  return (sys_ins_reg->flags & F_HASXT) != 0;
}