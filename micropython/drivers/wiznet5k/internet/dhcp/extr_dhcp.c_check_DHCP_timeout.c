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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_FAILED ; 
 int /*<<< orphan*/  DHCP_RUNNING ; 
 scalar_t__ DHCP_WAIT_TIME ; 
 scalar_t__ MAX_DHCP_RETRY ; 
#define  STATE_DHCP_DISCOVER 130 
 int STATE_DHCP_INIT ; 
#define  STATE_DHCP_REQUEST 129 
#define  STATE_DHCP_REREQUEST 128 
 scalar_t__ dhcp_retry_count ; 
 int dhcp_state ; 
 scalar_t__ dhcp_tick_1s ; 
 scalar_t__ dhcp_tick_next ; 
 int /*<<< orphan*/  reset_DHCP_timeout () ; 
 int /*<<< orphan*/  send_DHCP_DISCOVER () ; 
 int /*<<< orphan*/  send_DHCP_REQUEST () ; 

uint8_t check_DHCP_timeout(void)
{
	uint8_t ret = DHCP_RUNNING;
	
	if (dhcp_retry_count < MAX_DHCP_RETRY) {
		if (dhcp_tick_next < dhcp_tick_1s) {

			switch ( dhcp_state ) {
				case STATE_DHCP_DISCOVER :
//					printf("<<timeout>> state : STATE_DHCP_DISCOVER\r\n");
					send_DHCP_DISCOVER();
				break;
		
				case STATE_DHCP_REQUEST :
//					printf("<<timeout>> state : STATE_DHCP_REQUEST\r\n");

					send_DHCP_REQUEST();
				break;

				case STATE_DHCP_REREQUEST :
//					printf("<<timeout>> state : STATE_DHCP_REREQUEST\r\n");
					
					send_DHCP_REQUEST();
				break;
		
				default :
				break;
			}

			dhcp_tick_1s = 0;
			dhcp_tick_next = dhcp_tick_1s + DHCP_WAIT_TIME;
			dhcp_retry_count++;
		}
	} else { // timeout occurred

		switch(dhcp_state) {
			case STATE_DHCP_DISCOVER:
				dhcp_state = STATE_DHCP_INIT;
				ret = DHCP_FAILED;
				break;
			case STATE_DHCP_REQUEST:
			case STATE_DHCP_REREQUEST:
				send_DHCP_DISCOVER();
				dhcp_state = STATE_DHCP_DISCOVER;
				break;
			default :
				break;
		}
		reset_DHCP_timeout();
	}
	return ret;
}