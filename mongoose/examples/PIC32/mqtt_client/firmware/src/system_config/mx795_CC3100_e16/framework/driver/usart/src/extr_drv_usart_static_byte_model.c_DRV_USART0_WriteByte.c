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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_SOURCE_USART_2_TRANSMIT ; 
 scalar_t__ PLIB_USART_TransmitterBufferIsFull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_USART_TransmitterByteSend (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  SYS_INT_SourceEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_ID_2 ; 

void DRV_USART0_WriteByte(const uint8_t byte)
{
    /* Wait till TX buffer is available as blocking operation is selected */
    while(PLIB_USART_TransmitterBufferIsFull(USART_ID_2));
    /* Send one byte */
    PLIB_USART_TransmitterByteSend(USART_ID_2, byte);
    SYS_INT_SourceEnable(INT_SOURCE_USART_2_TRANSMIT);
}