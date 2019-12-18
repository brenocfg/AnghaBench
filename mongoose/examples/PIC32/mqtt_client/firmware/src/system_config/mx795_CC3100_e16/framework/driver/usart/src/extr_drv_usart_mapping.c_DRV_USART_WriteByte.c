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
typedef  int DRV_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_USART0_WriteByte (int /*<<< orphan*/  const) ; 
#define  DRV_USART_INDEX_0 128 

void DRV_USART_WriteByte( const DRV_HANDLE handle, const uint8_t byte)
{
    uintptr_t instance;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_USART_INDEX_0:
        {
            DRV_USART0_WriteByte(byte);
            break;
        }
        default:
        {
            break;
        }
    }
}