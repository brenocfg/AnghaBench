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
typedef  int /*<<< orphan*/  DRV_USART_LINE_CONTROL_SET_RESULT ;
typedef  int /*<<< orphan*/  DRV_USART_LINE_CONTROL ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_USART_LINE_CONTROL_SET_SUCCESS ; 
 int /*<<< orphan*/  PLIB_USART_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_USART_Enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_USART_LineControlModeSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PLIB_USART_ModuleIsBusy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_ID_2 ; 

DRV_USART_LINE_CONTROL_SET_RESULT DRV_USART0_LineControlSet(DRV_USART_LINE_CONTROL lineControlMode)
{
#if defined (PLIB_USART_ExistsModuleBusyStatus)
    bool isEnabled = false;
#endif
#if defined (PLIB_USART_ExistsModuleBusyStatus)
        isEnabled = PLIB_USART_ModuleIsBusy (USART_ID_2);
        if (isEnabled)
        {
            PLIB_USART_Disable (USART_ID_2);
            while (PLIB_USART_ModuleIsBusy (USART_ID_2));
        }
#endif

    /* Set the Line Control Mode */
    PLIB_USART_LineControlModeSelect(USART_ID_2, lineControlMode);
    
#if defined (PLIB_USART_ExistsModuleBusyStatus)
        if (isEnabled)
        {
            PLIB_USART_Enable (USART_ID_2);
        }
#endif

    /* Return success */
    return(DRV_USART_LINE_CONTROL_SET_SUCCESS);
}