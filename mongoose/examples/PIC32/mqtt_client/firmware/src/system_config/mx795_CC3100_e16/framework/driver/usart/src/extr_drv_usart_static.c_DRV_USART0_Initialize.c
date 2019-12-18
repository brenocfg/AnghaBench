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
typedef  int /*<<< orphan*/  SYS_MODULE_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_BUS_PERIPHERAL_1 ; 
 int /*<<< orphan*/  DRV_USART_INDEX_0 ; 
 int /*<<< orphan*/  DRV_USART_LINE_CONTROL_8NONE1 ; 
 int /*<<< orphan*/  INT_SOURCE_USART_2_ERROR ; 
 int /*<<< orphan*/  INT_SOURCE_USART_2_RECEIVE ; 
 int /*<<< orphan*/  INT_SOURCE_USART_2_TRANSMIT ; 
 int /*<<< orphan*/  PLIB_USART_BaudSetAndEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLIB_USART_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_USART_InitializeModeGeneral (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  PLIB_USART_InitializeOperation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_USART_LineControlModeSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_CLK_PeripheralFrequencyGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_INT_SourceEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_INT_SourceStatusClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_ENABLE_TX_RX_USED ; 
 int /*<<< orphan*/  USART_ID_2 ; 
 int /*<<< orphan*/  USART_RECEIVE_FIFO_ONE_CHAR ; 
 int /*<<< orphan*/  USART_TRANSMIT_FIFO_IDLE ; 

SYS_MODULE_OBJ DRV_USART0_Initialize(void)
{
    uint32_t clockSource;

    /* Disable the USART module to configure it*/
    PLIB_USART_Disable (USART_ID_2);

    /* Initialize the USART based on configuration settings */
    PLIB_USART_InitializeModeGeneral(USART_ID_2,
            false,  /*Auto baud*/
            false,  /*LoopBack mode*/
            false,  /*Auto wakeup on start*/
            false,  /*IRDA mode*/
            false);  /*Stop In Idle mode*/

    /* Set the line control mode */
    PLIB_USART_LineControlModeSelect(USART_ID_2, DRV_USART_LINE_CONTROL_8NONE1);

    /* We set the receive interrupt mode to receive an interrupt whenever FIFO
       is not empty */
    PLIB_USART_InitializeOperation(USART_ID_2,
            USART_RECEIVE_FIFO_ONE_CHAR,
            USART_TRANSMIT_FIFO_IDLE,
            USART_ENABLE_TX_RX_USED);

    /* Get the USART clock source value*/
    clockSource = SYS_CLK_PeripheralFrequencyGet ( CLK_BUS_PERIPHERAL_1 );

    /* Set the baud rate and enable the USART */
    PLIB_USART_BaudSetAndEnable(USART_ID_2,
            clockSource,
            115200);  /*Desired Baud rate value*/

    /* Clear the interrupts to be on the safer side*/
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_2_TRANSMIT);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_2_RECEIVE);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_2_ERROR);

    /* Enable the error interrupt source */
    SYS_INT_SourceEnable(INT_SOURCE_USART_2_ERROR);

    /* Enable the Receive interrupt source */
    SYS_INT_SourceEnable(INT_SOURCE_USART_2_RECEIVE);

    /* Return the driver instance value*/
    return (SYS_MODULE_OBJ)DRV_USART_INDEX_0;
}