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
struct TYPE_2__ {int /*<<< orphan*/  (* rx ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 TYPE_1__* current_hooks ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void safety_rx_hook(CAN_FIFOMailBox_TypeDef *to_push){
  current_hooks->rx(to_push);
}