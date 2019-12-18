#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int MCI_IDR; } ;
typedef  int /*<<< orphan*/  AT91PS_USART ;

/* Variables and functions */
 int /*<<< orphan*/  AT91C_AIC_PRIOR_HIGHEST ; 
 int /*<<< orphan*/  AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE ; 
 int /*<<< orphan*/  AT91C_BASE_AIC ; 
 scalar_t__ AT91C_BASE_DBGU ; 
 TYPE_1__* AT91C_BASE_MCI ; 
 int /*<<< orphan*/  AT91C_BASE_PDC_MCI ; 
 int /*<<< orphan*/  AT91C_BASE_PIOB ; 
 int /*<<< orphan*/  AT91C_ID_MCI ; 
 scalar_t__ AT91C_INIT_OK ; 
 int /*<<< orphan*/  AT91C_MCI_DTOR_1MEGA_CYCLES ; 
 int /*<<< orphan*/  AT91C_MCI_MR_PDCMODE ; 
 int /*<<< orphan*/  AT91C_MCI_SDCARD_4BITS_SLOTA ; 
 int /*<<< orphan*/  AT91C_PIO_PB7 ; 
 int /*<<< orphan*/  AT91F_AIC_ConfigureIt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91F_AIC_EnableIt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91F_ASM_MCI_Handler ; 
 int /*<<< orphan*/  AT91F_CfgDevice () ; 
 int /*<<< orphan*/  AT91F_MCI_CfgPIO () ; 
 int /*<<< orphan*/  AT91F_MCI_CfgPMC () ; 
 int /*<<< orphan*/  AT91F_MCI_Configure (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AT91F_MCI_SDCard_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AT91F_PDC_Open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91F_PIO_CfgOutput (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91F_PIO_SetOutput (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91F_US_EnableRx (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  MCI_Device ; 
 int TRUE ; 

int AT91F_MCI_Init(void)
{

///////////////////////////////////////////////////////////////////////////////////////////
//  MCI Init : common to MMC and SDCard
///////////////////////////////////////////////////////////////////////////////////////////

    // Set up PIO SDC_TYPE to switch on MMC/SDCard and not DataFlash Card
	AT91F_PIO_CfgOutput(AT91C_BASE_PIOB,AT91C_PIO_PB7);
	AT91F_PIO_SetOutput(AT91C_BASE_PIOB,AT91C_PIO_PB7);
	
	// Init MCI for MMC and SDCard interface
	AT91F_MCI_CfgPIO();	
	AT91F_MCI_CfgPMC();
	AT91F_PDC_Open(AT91C_BASE_PDC_MCI);

    // Disable all the interrupts
    AT91C_BASE_MCI->MCI_IDR = 0xFFFFFFFF;

	// Init MCI Device Structures
	AT91F_CfgDevice();

	// Configure MCI interrupt 
	AT91F_AIC_ConfigureIt(AT91C_BASE_AIC,
						 AT91C_ID_MCI,
						 AT91C_AIC_PRIOR_HIGHEST,
						 AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE,
						 AT91F_ASM_MCI_Handler);

	// Enable MCI interrupt
	AT91F_AIC_EnableIt(AT91C_BASE_AIC,AT91C_ID_MCI);

	// Enable Receiver
	AT91F_US_EnableRx((AT91PS_USART) AT91C_BASE_DBGU);

	AT91F_MCI_Configure(AT91C_BASE_MCI,
						AT91C_MCI_DTOR_1MEGA_CYCLES,
						AT91C_MCI_MR_PDCMODE,			// 15MHz for MCK = 60MHz (CLKDIV = 1)
						AT91C_MCI_SDCARD_4BITS_SLOTA);
	
	if(AT91F_MCI_SDCard_Init(&MCI_Device) != AT91C_INIT_OK)
		return FALSE;
	else
		return TRUE;

}