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
typedef  scalar_t__ LPVOID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DEV_BROADCAST_DEVICEINTERFACE ;

/* Variables and functions */
#define  DBT_DEVICEARRIVAL 128 
 int NO_ERROR ; 
 int ProcessDeviceArrival (int /*<<< orphan*/ *) ; 

DWORD
HandleDeviceEvent(
    DWORD dwEventType,
    LPVOID lpEventData)
{
    switch (dwEventType)
    {
        case DBT_DEVICEARRIVAL:
        {
            DEV_BROADCAST_DEVICEINTERFACE* incoming_device =
                (DEV_BROADCAST_DEVICEINTERFACE*)lpEventData;

            return ProcessDeviceArrival(incoming_device);
        }

        default :
        {
            break;
        }
    }

    return NO_ERROR;
}