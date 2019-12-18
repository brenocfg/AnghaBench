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
 int /*<<< orphan*/  CONNECTED_LED ; 
 int /*<<< orphan*/  LEDS_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEDS_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWIP_SYS_TIMER_INTERVAL ; 
 int /*<<< orphan*/  TCP_STATE_REQUEST_CONNECTION ; 
 int /*<<< orphan*/  app_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_sys_timer_id ; 
 int /*<<< orphan*/  m_tcp_state ; 
 int /*<<< orphan*/  sys_check_timeouts () ; 

void nrf51_driver_interface_up(void)
{
  uint32_t err_code;

  APPL_LOG ("[APPL]: IPv6 interface up.\r\n");

  sys_check_timeouts();

  m_tcp_state = TCP_STATE_REQUEST_CONNECTION;

  err_code = app_timer_start(m_sys_timer_id, LWIP_SYS_TIMER_INTERVAL, NULL);
  APP_ERROR_CHECK(err_code);

  LEDS_OFF(ADVERTISING_LED);
  LEDS_ON(CONNECTED_LED);
}