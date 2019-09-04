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
struct TYPE_2__ {unsigned short profiles; unsigned short mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 unsigned short THM_PROFILE_MAX ; 
 scalar_t__ sony_call_snc_handle (int,unsigned short,unsigned int*) ; 
 TYPE_1__* th_handle ; 

__attribute__((used)) static int sony_nc_thermal_mode_set(unsigned short mode)
{
	unsigned int result;

	/* the thermal profile seems to be a two bit bitmask:
	 * lsb -> silent
	 * msb -> performance
	 * no bit set is the normal operation and is always valid
	 * Some vaio models only have "balanced" and "performance"
	 */
	if ((mode && !(th_handle->profiles & mode)) || mode >= THM_PROFILE_MAX)
		return -EINVAL;

	if (sony_call_snc_handle(0x0122, mode << 0x10 | 0x0200, &result))
		return -EIO;

	th_handle->mode = mode;

	return 0;
}