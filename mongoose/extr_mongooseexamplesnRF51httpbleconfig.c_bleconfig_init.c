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

/* Variables and functions */
 int /*<<< orphan*/  APPL_LOG (char*) ; 
 int /*<<< orphan*/  advertising_init () ; 
 int /*<<< orphan*/  advertising_start () ; 
 int /*<<< orphan*/  app_trace_init () ; 
 int /*<<< orphan*/  ble_stack_init () ; 
 int /*<<< orphan*/  ip_stack_init () ; 
 int /*<<< orphan*/  leds_init () ; 
 int /*<<< orphan*/  scheduler_init () ; 
 int /*<<< orphan*/  timers_init () ; 

void bleconfig_init(void) {
  //Initialize.
  app_trace_init();
  leds_init();
  timers_init();
  ble_stack_init();
  advertising_init();
  ip_stack_init ();
  scheduler_init();

  APPL_LOG ("\r\n");
  APPL_LOG ("[APPL]: Init done.\r\n");

  //Start execution.
  advertising_start();
}