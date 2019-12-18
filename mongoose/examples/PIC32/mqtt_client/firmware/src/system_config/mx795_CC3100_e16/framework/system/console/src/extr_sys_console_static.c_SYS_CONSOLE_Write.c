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
 int /*<<< orphan*/  DRV_USART0_WriteByte (char const) ; 

ssize_t SYS_CONSOLE_Write(const SYS_MODULE_INDEX index, int fd, const char *buf, size_t count )
{
    size_t numBytes = 0;
    while( numBytes < count )
    {
        DRV_USART0_WriteByte(buf[numBytes++]);
    }
    return count;
}