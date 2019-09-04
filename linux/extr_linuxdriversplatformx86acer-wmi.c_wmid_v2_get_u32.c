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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
#define  ACER_CAP_BLUETOOTH 130 
#define  ACER_CAP_THREEG 129 
#define  ACER_CAP_WIRELESS 128 
 int /*<<< orphan*/  ACER_WMID3_GDS_BLUETOOTH ; 
 int /*<<< orphan*/  ACER_WMID3_GDS_THREEG ; 
 int /*<<< orphan*/  ACER_WMID3_GDS_WIRELESS ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  wmid3_get_device_status (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status wmid_v2_get_u32(u32 *value, u32 cap)
{
	u16 device;

	switch (cap) {
	case ACER_CAP_WIRELESS:
		device = ACER_WMID3_GDS_WIRELESS;
		break;
	case ACER_CAP_BLUETOOTH:
		device = ACER_WMID3_GDS_BLUETOOTH;
		break;
	case ACER_CAP_THREEG:
		device = ACER_WMID3_GDS_THREEG;
		break;
	default:
		return AE_ERROR;
	}
	return wmid3_get_device_status(value, device);
}