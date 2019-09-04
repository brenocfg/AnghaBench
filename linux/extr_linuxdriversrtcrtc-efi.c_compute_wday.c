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
struct TYPE_3__ {int year; } ;
typedef  TYPE_1__ efi_time_t ;

/* Variables and functions */

__attribute__((used)) static int
compute_wday(efi_time_t *eft, int yday)
{
	int ndays = eft->year * (365 % 7)
		    + (eft->year - 1) / 4
		    - (eft->year - 1) / 100
		    + (eft->year - 1) / 400
		    + yday;

	/*
	 * 1/1/0000 may or may not have been a Sunday (if it ever existed at
	 * all) but assuming it was makes this calculation work correctly.
	 */
	return ndays % 7;
}