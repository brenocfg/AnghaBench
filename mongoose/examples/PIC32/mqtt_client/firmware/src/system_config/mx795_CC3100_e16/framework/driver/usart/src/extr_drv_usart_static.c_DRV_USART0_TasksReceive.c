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
 int /*<<< orphan*/  INT_SOURCE_USART_2_RECEIVE ; 
 int /*<<< orphan*/  SYS_INT_SourceStatusClear (int /*<<< orphan*/ ) ; 
 scalar_t__ SYS_INT_SourceStatusGet (int /*<<< orphan*/ ) ; 

void DRV_USART0_TasksReceive(void)
{
    /* This is the USART Driver Receive tasks routine. If the receive
       interrupt flag is set, the tasks routines are executed.
     */

    /* Reading the receive interrupt flag */
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_2_RECEIVE))
    {

        /* Clear up the interrupt flag */
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_2_RECEIVE);
    }
}