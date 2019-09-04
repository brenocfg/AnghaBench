#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* interfaces; } ;
typedef  TYPE_2__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
typedef  size_t xtensa_interface ;
struct TYPE_4__ {int class_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_INTERFACE (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTENSA_UNDEFINED ; 

int
xtensa_interface_class_id (xtensa_isa isa, xtensa_interface intf)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  CHECK_INTERFACE (intisa, intf, XTENSA_UNDEFINED);
  return intisa->interfaces[intf].class_id;
}