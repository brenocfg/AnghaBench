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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int (* tx_lin ) (int,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 TYPE_1__* current_hooks ; 
 int stub1 (int,int /*<<< orphan*/ *,int) ; 

int safety_tx_lin_hook(int lin_num, uint8_t *data, int len){
  return current_hooks->tx_lin(lin_num, data, len);
}