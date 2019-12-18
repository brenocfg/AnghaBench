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
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  DRV_USART_BAUD_SET_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_BUS_PERIPHERAL_1 ; 
 int /*<<< orphan*/  DRV_USART_BAUD_SET_ERROR ; 
 int /*<<< orphan*/  DRV_USART_BAUD_SET_SUCCESS ; 
 int /*<<< orphan*/  PLIB_USART_BaudRateHighDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_USART_BaudRateHighEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_USART_BaudRateHighSet (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PLIB_USART_BaudRateSet (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PLIB_USART_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_USART_Enable (int /*<<< orphan*/ ) ; 
 int PLIB_USART_ModuleIsBusy (int /*<<< orphan*/ ) ; 
 int SYS_CLK_PeripheralFrequencyGet (int /*<<< orphan*/ ) ; 
 int UINT16_MAX ; 
 int /*<<< orphan*/  USART_ID_2 ; 

DRV_USART_BAUD_SET_RESULT DRV_USART0_BaudSet(uint32_t baud)
{
    uint32_t clockSource;
    int32_t brgValueLow=0;
    int32_t brgValueHigh=0;
    DRV_USART_BAUD_SET_RESULT retVal = DRV_USART_BAUD_SET_SUCCESS;
#if defined (PLIB_USART_ExistsModuleBusyStatus)
    bool isEnabled = false;
#endif

    /* Get the USART clock source value*/
    clockSource = SYS_CLK_PeripheralFrequencyGet ( CLK_BUS_PERIPHERAL_1 );

    /* Calculate low and high baud values */
    brgValueLow  = ( (clockSource/baud) >> 4 ) - 1;
    brgValueHigh = ( (clockSource/baud) >> 2 ) - 1;

#if defined (PLIB_USART_ExistsModuleBusyStatus)
        isEnabled = PLIB_USART_ModuleIsBusy (USART_ID_2);
        if (isEnabled)
        {
            PLIB_USART_Disable (USART_ID_2);
            while (PLIB_USART_ModuleIsBusy (USART_ID_2));
        }
#endif

    /* Check if the baud value can be set with high baud settings */
    if ((brgValueHigh >= 0) && (brgValueHigh <= UINT16_MAX))
    {
        PLIB_USART_BaudRateHighEnable(USART_ID_2);
        PLIB_USART_BaudRateHighSet(USART_ID_2,clockSource,baud);
    }
    
    /* Check if the baud value can be set with low baud settings */
    else if ((brgValueLow >= 0) && (brgValueLow <= UINT16_MAX))
    {
        PLIB_USART_BaudRateHighDisable(USART_ID_2);
        PLIB_USART_BaudRateSet(USART_ID_2, clockSource, baud);
    }
    else
    {
            retVal = DRV_USART_BAUD_SET_ERROR;
    }

#if defined (PLIB_USART_ExistsModuleBusyStatus)
    if (isEnabled)
    {
        PLIB_USART_Enable (USART_ID_2);
    }
#endif

    return retVal;
}