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
struct tcp_pcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTED_LED ; 
 int DISPLAY_LED_0 ; 
 int DISPLAY_LED_1 ; 
 int DISPLAY_LED_2 ; 
 int DISPLAY_LED_3 ; 
 int /*<<< orphan*/  LEDS_OFF (int) ; 
 int /*<<< orphan*/  LEDS_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_STATE_REQUEST_CONNECTION ; 
 int /*<<< orphan*/  UNUSED_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tcp_state ; 
 int /*<<< orphan*/  tcp_arg (struct tcp_pcb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_close (struct tcp_pcb*) ; 
 int /*<<< orphan*/  tcp_err (struct tcp_pcb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_poll (struct tcp_pcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_recv (struct tcp_pcb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_sent (struct tcp_pcb*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcp_port_close(struct tcp_pcb * p_pcb)
{
  m_tcp_state = TCP_STATE_REQUEST_CONNECTION;

  //Reset all information set on and/or callback registered for the  port.
  tcp_arg(p_pcb, NULL);
  tcp_sent(p_pcb, NULL);
  tcp_recv(p_pcb, NULL);
  tcp_err(p_pcb, NULL);
  tcp_poll(p_pcb, NULL, 0);

  UNUSED_VARIABLE(tcp_close(p_pcb));

  LEDS_OFF((DISPLAY_LED_0 | DISPLAY_LED_1 | DISPLAY_LED_2 | DISPLAY_LED_3));
  LEDS_ON(CONNECTED_LED);
}