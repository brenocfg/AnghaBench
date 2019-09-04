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
 int /*<<< orphan*/  ADVERTISING_LED ; 
 int /*<<< orphan*/  APPL_LOG (char*) ; 
 int /*<<< orphan*/  APP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int DISPLAY_LED_0 ; 
 int DISPLAY_LED_1 ; 
 int DISPLAY_LED_2 ; 
 int DISPLAY_LED_3 ; 
 int /*<<< orphan*/  LEDS_OFF (int) ; 
 int /*<<< orphan*/  LEDS_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  app_timer_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_sys_timer_id ; 
 int /*<<< orphan*/  m_tcp_state ; 

void nrf51_driver_interface_down(void)
{
  uint32_t err_code;

  APPL_LOG ("[APPL]: IPv6 interface down.\r\n");

  err_code = app_timer_stop(m_sys_timer_id);
  APP_ERROR_CHECK(err_code);

  LEDS_OFF((DISPLAY_LED_0 | DISPLAY_LED_1 | DISPLAY_LED_2 | DISPLAY_LED_3));
  LEDS_ON(ADVERTISING_LED);

  m_tcp_state = TCP_STATE_DISCONNECTED;
}