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
typedef  int /*<<< orphan*/  timelib_sll ;

/* Variables and functions */
 int /*<<< orphan*/  timelib_daynr_from_weeknr_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

timelib_sll timelib_daynr_from_weeknr(timelib_sll iy, timelib_sll iw, timelib_sll id)
{
	timelib_sll dummy_iso_year;

	return timelib_daynr_from_weeknr_ex(iy, iw, id, &dummy_iso_year);
}