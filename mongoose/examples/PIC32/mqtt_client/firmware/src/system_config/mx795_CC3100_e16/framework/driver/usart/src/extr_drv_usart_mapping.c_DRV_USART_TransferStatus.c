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
typedef  int /*<<< orphan*/  DRV_USART_TRANSFER_STATUS ;
typedef  int DRV_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_USART0_TransferStatus () ; 
#define  DRV_USART_INDEX_0 128 

DRV_USART_TRANSFER_STATUS DRV_USART_TransferStatus( const DRV_HANDLE handle )
{
    uintptr_t instance;
    DRV_USART_TRANSFER_STATUS returnValue;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_USART_INDEX_0:
        {
            returnValue = DRV_USART0_TransferStatus();
            break;
        }
        default:
        {
            returnValue = (DRV_USART_TRANSFER_STATUS)NULL;
            break;
        }
    }
    return returnValue;
}