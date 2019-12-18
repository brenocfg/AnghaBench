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
 int /*<<< orphan*/  PLIB_USART_ReceiverDataIsAvailable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_ID_2 ; 

bool DRV_USART0_ReceiverBufferIsEmpty( void )
{
    /* Check the status of receiver buffer */
    return(!PLIB_USART_ReceiverDataIsAvailable(USART_ID_2));
}