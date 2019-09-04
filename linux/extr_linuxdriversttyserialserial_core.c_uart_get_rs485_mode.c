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
typedef  void* u32 ;
struct serial_rs485 {int flags; void* delay_rts_after_send; void* delay_rts_before_send; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_AFTER_SEND ; 
 int SER_RS485_RTS_ON_SEND ; 
 int SER_RS485_RX_DURING_TX ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 int device_property_read_u32_array (struct device*,char*,void**,int) ; 

void uart_get_rs485_mode(struct device *dev, struct serial_rs485 *rs485conf)
{
	u32 rs485_delay[2];
	int ret;

	ret = device_property_read_u32_array(dev, "rs485-rts-delay",
					     rs485_delay, 2);
	if (!ret) {
		rs485conf->delay_rts_before_send = rs485_delay[0];
		rs485conf->delay_rts_after_send = rs485_delay[1];
	} else {
		rs485conf->delay_rts_before_send = 0;
		rs485conf->delay_rts_after_send = 0;
	}

	/*
	 * Clear full-duplex and enabled flags, set RTS polarity to active high
	 * to get to a defined state with the following properties:
	 */
	rs485conf->flags &= ~(SER_RS485_RX_DURING_TX | SER_RS485_ENABLED |
			      SER_RS485_RTS_AFTER_SEND);
	rs485conf->flags |= SER_RS485_RTS_ON_SEND;

	if (device_property_read_bool(dev, "rs485-rx-during-tx"))
		rs485conf->flags |= SER_RS485_RX_DURING_TX;

	if (device_property_read_bool(dev, "linux,rs485-enabled-at-boot-time"))
		rs485conf->flags |= SER_RS485_ENABLED;

	if (device_property_read_bool(dev, "rs485-rts-active-low")) {
		rs485conf->flags &= ~SER_RS485_RTS_ON_SEND;
		rs485conf->flags |= SER_RS485_RTS_AFTER_SEND;
	}
}