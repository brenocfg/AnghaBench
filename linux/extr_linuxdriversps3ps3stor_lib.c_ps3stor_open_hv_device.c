#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ps3_system_bus_device {scalar_t__ match_id; } ;
struct TYPE_2__ {int flash_open; int disk_open; } ;

/* Variables and functions */
 scalar_t__ PS3_MATCH_ID_STOR_DISK ; 
 scalar_t__ PS3_MATCH_ID_STOR_FLASH ; 
 TYPE_1__ ps3_flash_workaround ; 
 int ps3_open_hv_device (struct ps3_system_bus_device*) ; 

__attribute__((used)) static int ps3stor_open_hv_device(struct ps3_system_bus_device *sbd)
{
	int error = ps3_open_hv_device(sbd);

	if (error)
		return error;

	if (sbd->match_id == PS3_MATCH_ID_STOR_FLASH)
		ps3_flash_workaround.flash_open = 1;

	if (sbd->match_id == PS3_MATCH_ID_STOR_DISK)
		ps3_flash_workaround.disk_open = 1;

	return 0;
}