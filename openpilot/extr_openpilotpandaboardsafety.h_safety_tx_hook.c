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
struct TYPE_2__ {int (* tx ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 TYPE_1__* current_hooks ; 
 int stub1 (int /*<<< orphan*/ *) ; 

int safety_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {
  return current_hooks->tx(to_send);
}