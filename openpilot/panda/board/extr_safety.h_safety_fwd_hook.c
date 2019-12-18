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
struct TYPE_2__ {int (* fwd ) (int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 TYPE_1__* current_hooks ; 
 int stub1 (int,int /*<<< orphan*/ *) ; 

int safety_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {
  return current_hooks->fwd(bus_num, to_fwd);
}