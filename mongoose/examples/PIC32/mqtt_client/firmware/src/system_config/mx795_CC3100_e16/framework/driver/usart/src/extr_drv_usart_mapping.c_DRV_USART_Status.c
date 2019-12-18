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
typedef  int /*<<< orphan*/  SYS_STATUS ;
typedef  int SYS_MODULE_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_USART0_Status () ; 
#define  DRV_USART_INDEX_0 128 
 int /*<<< orphan*/  SYS_STATUS_ERROR ; 

SYS_STATUS DRV_USART_Status( SYS_MODULE_OBJ object)
{
    SYS_STATUS returnValue;

    switch(object)
    {
        case DRV_USART_INDEX_0:
        {
            returnValue = DRV_USART0_Status();
            break;
        }
        default:
        {
            returnValue = SYS_STATUS_ERROR;
            break;
        }
    }
    return returnValue;
}