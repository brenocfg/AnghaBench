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
struct TYPE_2__ {int /*<<< orphan*/  (* set_value_all ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ led_matrix_driver ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void led_matrix_set_index_value_all(uint8_t value) { led_matrix_driver.set_value_all(value); }