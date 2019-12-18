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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  SYS_MODULE_INDEX ;

/* Variables and functions */
 char DRV_USART0_ReadByte () ; 
 int /*<<< orphan*/  DRV_USART0_ReceiverBufferIsEmpty () ; 

ssize_t SYS_CONSOLE_Read(const SYS_MODULE_INDEX index, int fd, void *buf, size_t count )
{
    size_t  numBytes = 0;
    char* pReadByte = (char*)buf;
	if( !DRV_USART0_ReceiverBufferIsEmpty() )
	{
		*pReadByte = DRV_USART0_ReadByte();

		numBytes++;
		pReadByte++;
    }

    return numBytes;
}