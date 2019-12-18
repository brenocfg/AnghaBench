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
typedef  int /*<<< orphan*/  AT91PS_USART ;

/* Variables and functions */
 int /*<<< orphan*/  AT91C_MASTER_CLOCK ; 
 int /*<<< orphan*/  AT91C_US_ASYNC_MODE ; 
 int /*<<< orphan*/  AT91F_DBGU_CfgPIO () ; 
 int /*<<< orphan*/  AT91F_US0_CfgPIO () ; 
 int /*<<< orphan*/  AT91F_US0_CfgPMC () ; 
 int /*<<< orphan*/  AT91F_US_Configure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91F_US_EnableRx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91F_US_EnableTx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91F_US_ResetRx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91F_US_ResetTx (int /*<<< orphan*/ ) ; 
 int MAX_UARTS ; 
 scalar_t__ port_detected ; 
 scalar_t__ us ; 
 scalar_t__* usa ; 

void at91_init_uarts(void)
{
	int i;

	port_detected = 0;
	AT91F_DBGU_CfgPIO();
	AT91F_US0_CfgPIO();
	AT91F_US0_CfgPMC();

	for(i=0; i<MAX_UARTS; i++) {
		us = usa[i];
		AT91F_US_ResetRx((AT91PS_USART)us);
		AT91F_US_ResetTx((AT91PS_USART)us);

		// Configure DBGU
		AT91F_US_Configure(
			(AT91PS_USART)us, // DBGU base address
			AT91C_MASTER_CLOCK,            // 60 MHz
			AT91C_US_ASYNC_MODE,           // mode Register to be programmed
			115200,                        // baudrate to be programmed
			0                              // timeguard to be programmed
			);

		// Enable Transmitter
		AT91F_US_EnableTx((AT91PS_USART)us);
		// Enable Receiver
		AT91F_US_EnableRx((AT91PS_USART)us);
	}
	us = usa[0];
}