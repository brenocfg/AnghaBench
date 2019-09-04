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
typedef  enum toshiba_iio_accel_chan { ____Placeholder_toshiba_iio_accel_chan } toshiba_iio_accel_chan ;

/* Variables and functions */
#define  AXIS_X 130 
#define  AXIS_Y 129 
#define  AXIS_Z 128 
 int HCI_ACCEL_DIRECTION_MASK ; 
 int HCI_ACCEL_MASK ; 
 int HCI_MISC_SHIFT ; 
 int toshiba_accelerometer_get (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  toshiba_acpi ; 

__attribute__((used)) static int toshiba_iio_accel_get_axis(enum toshiba_iio_accel_chan chan)
{
	u32 xyval, zval;
	int ret;

	ret = toshiba_accelerometer_get(toshiba_acpi, &xyval, &zval);
	if (ret < 0)
		return ret;

	switch (chan) {
	case AXIS_X:
		return xyval & HCI_ACCEL_DIRECTION_MASK ?
			-(xyval & HCI_ACCEL_MASK) : xyval & HCI_ACCEL_MASK;
	case AXIS_Y:
		return (xyval >> HCI_MISC_SHIFT) & HCI_ACCEL_DIRECTION_MASK ?
			-((xyval >> HCI_MISC_SHIFT) & HCI_ACCEL_MASK) :
			(xyval >> HCI_MISC_SHIFT) & HCI_ACCEL_MASK;
	case AXIS_Z:
		return zval & HCI_ACCEL_DIRECTION_MASK ?
			-(zval & HCI_ACCEL_MASK) : zval & HCI_ACCEL_MASK;
	}

	return ret;
}