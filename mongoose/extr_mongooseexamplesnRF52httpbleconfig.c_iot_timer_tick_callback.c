#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  APP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED_VARIABLE (void*) ; 
 int /*<<< orphan*/  iot_timer_update () ; 

__attribute__((used)) static void iot_timer_tick_callback(void * p_context)
{
  UNUSED_VARIABLE(p_context);

  uint32_t err_code = iot_timer_update();
  APP_ERROR_CHECK(err_code);
}