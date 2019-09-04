#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list_entry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  deviceid; } ;
struct TYPE_5__ {TYPE_1__ device; } ;
typedef  TYPE_2__ pnfs_file_device ;

/* Variables and functions */
 int /*<<< orphan*/  PNFS_DEVICEID_SIZE ; 
 TYPE_2__* device_entry (struct list_entry const*) ; 
 int memcmp (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int deviceid_compare(
    const struct list_entry *entry,
    const void *deviceid)
{
    const pnfs_file_device *device = device_entry(entry);
    return memcmp(device->device.deviceid, deviceid, PNFS_DEVICEID_SIZE);
}