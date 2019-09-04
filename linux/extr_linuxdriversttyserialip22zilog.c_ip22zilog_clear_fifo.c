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
struct zilog_channel {int /*<<< orphan*/  control; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 unsigned char CRC_ERR ; 
 int /*<<< orphan*/  ERR_RES ; 
 unsigned char PAR_ERR ; 
 int /*<<< orphan*/  R1 ; 
 unsigned char Rx_CH_AV ; 
 unsigned char Rx_OVR ; 
 int /*<<< orphan*/  ZSDELAY () ; 
 int /*<<< orphan*/  ZS_WSYNC (struct zilog_channel*) ; 
 unsigned char read_zsreg (struct zilog_channel*,int /*<<< orphan*/ ) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip22zilog_clear_fifo(struct zilog_channel *channel)
{
	int i;

	for (i = 0; i < 32; i++) {
		unsigned char regval;

		regval = readb(&channel->control);
		ZSDELAY();
		if (regval & Rx_CH_AV)
			break;

		regval = read_zsreg(channel, R1);
		readb(&channel->data);
		ZSDELAY();

		if (regval & (PAR_ERR | Rx_OVR | CRC_ERR)) {
			writeb(ERR_RES, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);
		}
	}
}