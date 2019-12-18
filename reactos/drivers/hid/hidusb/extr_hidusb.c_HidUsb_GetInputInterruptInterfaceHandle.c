#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_6__ {size_t NumberOfPipes; TYPE_1__* Pipes; } ;
struct TYPE_5__ {scalar_t__ PipeType; int EndpointAddress; } ;
typedef  TYPE_1__* PUSBD_PIPE_INFORMATION ;
typedef  TYPE_2__* PUSBD_INTERFACE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (size_t) ; 
 int USB_ENDPOINT_DIRECTION_MASK ; 
 scalar_t__ UsbdPipeTypeInterrupt ; 

PUSBD_PIPE_INFORMATION
HidUsb_GetInputInterruptInterfaceHandle(
    PUSBD_INTERFACE_INFORMATION InterfaceInformation)
{
    ULONG Index;

    //
    // sanity check
    //
    ASSERT(InterfaceInformation->NumberOfPipes);

    for (Index = 0; Index < InterfaceInformation->NumberOfPipes; Index++)
    {
        //DPRINT1("[HIDUSB] EndpointAddress %x PipeType %x PipeHandle %x\n", InterfaceInformation->Pipes[Index].EndpointAddress, InterfaceInformation->Pipes[Index].PipeType, InterfaceInformation->Pipes[Index].PipeHandle);
        if (InterfaceInformation->Pipes[Index].PipeType == UsbdPipeTypeInterrupt && (InterfaceInformation->Pipes[Index].EndpointAddress & USB_ENDPOINT_DIRECTION_MASK))
        {
            //
            // found handle
            //
            return &InterfaceInformation->Pipes[Index];
        }
    }

    //
    // not found
    //
    return NULL;
}