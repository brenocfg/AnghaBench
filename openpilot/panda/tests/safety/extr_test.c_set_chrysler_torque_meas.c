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
struct TYPE_2__ {int min; int max; } ;

/* Variables and functions */
 TYPE_1__ chrysler_torque_meas ; 

void set_chrysler_torque_meas(int min, int max){
  chrysler_torque_meas.min = min;
  chrysler_torque_meas.max = max;
}