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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int BitStuffTime (int) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 int /*<<< orphan*/  FS_LS_HOST_DELAY ; 
 int /*<<< orphan*/  HS_HOST_DELAY ; 
 int HUB_LS_SETUP ; 
 int /*<<< orphan*/  NS_TO_US (unsigned long) ; 
#define  USB_SPEED_FULL 130 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_LOW 128 

__attribute__((used)) static uint32_t calc_bus_time(int speed, int is_in, int is_isoc, int bytecount)
{
	unsigned long retval;

	switch (speed) {
	case USB_SPEED_HIGH:
		if (is_isoc) {
			retval =
			    ((38 * 8 * 2083) +
			     (2083 * (3 + BitStuffTime(bytecount)))) / 1000 +
			    HS_HOST_DELAY;
		} else {
			retval =
			    ((55 * 8 * 2083) +
			     (2083 * (3 + BitStuffTime(bytecount)))) / 1000 +
			    HS_HOST_DELAY;
		}
		break;
	case USB_SPEED_FULL:
		if (is_isoc) {
			retval =
			    (8354 * (31 + 10 * BitStuffTime(bytecount))) / 1000;
			if (is_in) {
				retval = 7268 + FS_LS_HOST_DELAY + retval;
			} else {
				retval = 6265 + FS_LS_HOST_DELAY + retval;
			}
		} else {
			retval =
			    (8354 * (31 + 10 * BitStuffTime(bytecount))) / 1000;
			retval = 9107 + FS_LS_HOST_DELAY + retval;
		}
		break;
	case USB_SPEED_LOW:
		if (is_in) {
			retval =
			    (67667 * (31 + 10 * BitStuffTime(bytecount))) /
			    1000;
			retval =
			    64060 + (2 * HUB_LS_SETUP) + FS_LS_HOST_DELAY +
			    retval;
		} else {
			retval =
			    (66700 * (31 + 10 * BitStuffTime(bytecount))) /
			    1000;
			retval =
			    64107 + (2 * HUB_LS_SETUP) + FS_LS_HOST_DELAY +
			    retval;
		}
		break;
	default:
		DWC_WARN("Unknown device speed\n");
		retval = -1;
	}

	return NS_TO_US(retval);
}