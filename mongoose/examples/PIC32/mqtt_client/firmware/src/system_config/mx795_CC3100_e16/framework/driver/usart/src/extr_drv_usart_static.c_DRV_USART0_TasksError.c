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
 int /*<<< orphan*/  INT_SOURCE_USART_2_ERROR ; 
 int /*<<< orphan*/  PLIB_USART_ReceiverOverrunErrorClear (int /*<<< orphan*/ ) ; 
 scalar_t__ PLIB_USART_ReceiverOverrunHasOccurred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_INT_SourceStatusClear (int /*<<< orphan*/ ) ; 
 scalar_t__ SYS_INT_SourceStatusGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_ID_2 ; 

void DRV_USART0_TasksError(void)
{
    /* This is the USART Driver Error tasks routine. In this function, the
     * driver checks if an error interrupt has occurred. If so the error
     * condition is cleared.  */

    /* Reading the error interrupt flag */
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_2_ERROR))
    {
        /* This means an error has occurred */
        if(PLIB_USART_ReceiverOverrunHasOccurred(USART_ID_2))
        {
            PLIB_USART_ReceiverOverrunErrorClear(USART_ID_2);
        }

        /* Clear up the error interrupt flag */
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_2_ERROR);
    }
}