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
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_SOFT_RESET ; 
 int ISD200_ERROR ; 
 int ISD200_GOOD ; 
 int ISD200_TRANSPORT_GOOD ; 
 int isd200_action (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

__attribute__((used)) static int isd200_atapi_soft_reset( struct us_data *us ) 
{
	int retStatus = ISD200_GOOD;
	int transferStatus;

	usb_stor_dbg(us, "Entering isd200_atapi_soft_reset\n");

	transferStatus = isd200_action( us, ACTION_SOFT_RESET, NULL, 0 );
	if (transferStatus != ISD200_TRANSPORT_GOOD) {
		usb_stor_dbg(us, "   Error issuing Atapi Soft Reset\n");
		retStatus = ISD200_ERROR;
	}

	usb_stor_dbg(us, "Leaving isd200_atapi_soft_reset %08X\n", retStatus);
	return retStatus;
}