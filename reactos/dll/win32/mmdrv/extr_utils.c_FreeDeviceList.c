#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ DeviceInstanceData; struct TYPE_3__* Next; } ;
typedef  TYPE_1__* PDEVICE_LIST ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 TYPE_1__* DeviceList ; 
 int /*<<< orphan*/  Heap ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID FreeDeviceList()
{
    PDEVICE_LIST pDevice;

    DPRINT("FreeDeviceList()\n");
    
    while (DeviceList)
    {
        pDevice = DeviceList;
        DeviceList = pDevice->Next;

        if (pDevice->DeviceInstanceData)
            HeapFree(Heap, 0, (LPVOID)pDevice->DeviceInstanceData);

        HeapFree(Heap, 0, (LPSTR)pDevice);
    }
}