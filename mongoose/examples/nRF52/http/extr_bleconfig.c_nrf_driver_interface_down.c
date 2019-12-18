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
 int DISPLAY_LED_0 ; 
 int DISPLAY_LED_1 ; 
 int DISPLAY_LED_2 ; 
 int DISPLAY_LED_3 ; 
 int /*<<< orphan*/  JOINING_MODE_TIMER_START ; 
 int /*<<< orphan*/  LEDS_OFF (int) ; 
 int /*<<< orphan*/  LEDS_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_ONE ; 
 int /*<<< orphan*/  TCP_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  commissioning_joining_mode_timer_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tcp_state ; 

void nrf_driver_interface_down(void)
{
#ifdef COMMISSIONING_ENABLED
  commissioning_joining_mode_timer_ctrl(JOINING_MODE_TIMER_START);
#endif // COMMISSIONING_ENABLED

  APPL_LOG ("[APPL]: IPv6 interface down.\r\n");

  LEDS_OFF((DISPLAY_LED_0 | DISPLAY_LED_1 | DISPLAY_LED_2 | DISPLAY_LED_3));
  LEDS_ON(LED_ONE);

  m_tcp_state = TCP_STATE_DISCONNECTED;
}