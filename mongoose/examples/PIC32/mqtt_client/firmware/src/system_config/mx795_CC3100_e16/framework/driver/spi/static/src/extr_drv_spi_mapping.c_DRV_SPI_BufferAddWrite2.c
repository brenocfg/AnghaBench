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
typedef  int /*<<< orphan*/  DRV_SPI_BUFFER_HANDLE ;
typedef  int /*<<< orphan*/  DRV_SPI_BUFFER_EVENT_HANDLER ;
typedef  int DRV_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI0_BufferAddWrite2 (void*,size_t,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRV_SPI_BUFFER_HANDLE_INVALID ; 
#define  DRV_SPI_INDEX_0 128 

DRV_SPI_BUFFER_HANDLE DRV_SPI_BufferAddWrite2 ( DRV_HANDLE handle,void *txBuffer,size_t size,DRV_SPI_BUFFER_EVENT_HANDLER completeCB,void * context, DRV_SPI_BUFFER_HANDLE * jobHandle)
{
    uintptr_t instance;
    DRV_SPI_BUFFER_HANDLE returnValue;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_SPI_INDEX_0:
        {
            returnValue = DRV_SPI0_BufferAddWrite2 ( txBuffer, size, completeCB, context, jobHandle);
            break;
        }
        default:
        {
            returnValue = DRV_SPI_BUFFER_HANDLE_INVALID;
            break;
        }
    }
    return returnValue;
}