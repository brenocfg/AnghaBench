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
struct TYPE_2__ {int num_regfiles; } ;
typedef  TYPE_1__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;

/* Variables and functions */

int
xtensa_isa_num_regfiles (xtensa_isa isa)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  return intisa->num_regfiles;
}