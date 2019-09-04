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
typedef  int /*<<< orphan*/  notification_filter ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int dbcc_size; TYPE_1__ dbcc_classguid; int /*<<< orphan*/  dbcc_devicetype; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_1__ GUID ;
typedef  TYPE_2__ DEV_BROADCAST_DEVICEINTERFACE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DBT_DEVTYP_DEVICEINTERFACE ; 
 int /*<<< orphan*/  DEVICE_NOTIFY_SERVICE_HANDLE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * RegisterDeviceNotificationW (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATIC_KSCATEGORY_AUDIO ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * device_notification_handle ; 
 int /*<<< orphan*/  logmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ service_status_handle ; 

BOOL
RegisterForDeviceNotifications()
{
    DEV_BROADCAST_DEVICEINTERFACE notification_filter;

    const GUID wdmaud_guid = {STATIC_KSCATEGORY_AUDIO};

    ZeroMemory(&notification_filter, sizeof(notification_filter));
    notification_filter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    notification_filter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    notification_filter.dbcc_classguid = wdmaud_guid;

    device_notification_handle =
        RegisterDeviceNotificationW((HANDLE) service_status_handle,
                                    &notification_filter,
                                    DEVICE_NOTIFY_SERVICE_HANDLE
/* |
                                   DEVICE_NOTIFY_ALL_INTERFACE_CLASSES*/);

    if ( ! device_notification_handle )
    {
        logmsg("RegisterDeviceNotification() failed with error %d\n", GetLastError());
    }

    return ( device_notification_handle != NULL );
}