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
struct TYPE_3__ {int /*<<< orphan*/  dbcc_name; } ;
typedef  int /*<<< orphan*/  PnP_AudioDevice ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DEV_BROADCAST_DEVICEINTERFACE ;

/* Variables and functions */
 int /*<<< orphan*/  AppendAudioDeviceToList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateDeviceDescriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyDeviceDescriptor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 

DWORD
ProcessDeviceArrival(DEV_BROADCAST_DEVICEINTERFACE* device)
{
    PnP_AudioDevice* list_node;
    list_node = CreateDeviceDescriptor(device->dbcc_name, TRUE);
    AppendAudioDeviceToList(list_node);
    DestroyDeviceDescriptor(list_node);

    return NO_ERROR;
}