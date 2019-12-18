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
 int /*<<< orphan*/  JOINING_MODE_TIMER_STOP_RESET ; 
 int /*<<< orphan*/  LEDS_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEDS_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_ONE ; 
 int /*<<< orphan*/  LED_TWO ; 
 int /*<<< orphan*/  TCP_STATE_REQUEST_CONNECTION ; 
 int /*<<< orphan*/  commissioning_joining_mode_timer_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tcp_state ; 
 int /*<<< orphan*/  sys_check_timeouts () ; 

void nrf_driver_interface_up(void)
{
#ifdef COMMISSIONING_ENABLED
  commissioning_joining_mode_timer_ctrl(JOINING_MODE_TIMER_STOP_RESET);
#endif // COMMISSIONING_ENABLED

  APPL_LOG ("[APPL]: IPv6 interface up.\r\n");

  sys_check_timeouts();

  m_tcp_state = TCP_STATE_REQUEST_CONNECTION;

  LEDS_OFF(LED_ONE);
  LEDS_ON(LED_TWO);
}