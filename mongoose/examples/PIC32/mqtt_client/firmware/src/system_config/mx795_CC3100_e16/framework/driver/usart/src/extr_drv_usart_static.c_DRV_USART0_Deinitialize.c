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
 int /*<<< orphan*/  INT_SOURCE_USART_2_RECEIVE ; 
 int /*<<< orphan*/  INT_SOURCE_USART_2_TRANSMIT ; 
 int /*<<< orphan*/  PLIB_USART_Disable (int /*<<< orphan*/ ) ; 
 int SYS_INT_SourceDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_ID_2 ; 

void  DRV_USART0_Deinitialize(void)
{
    bool status;

    /* Disable the interrupts */
    status = SYS_INT_SourceDisable(INT_SOURCE_USART_2_TRANSMIT) ;
    status = SYS_INT_SourceDisable(INT_SOURCE_USART_2_RECEIVE) ;
    status = SYS_INT_SourceDisable(INT_SOURCE_USART_2_ERROR);
    /* Ignore the warning */
    (void)status;

    /* Disable USART module */
    PLIB_USART_Disable (USART_ID_2);

}