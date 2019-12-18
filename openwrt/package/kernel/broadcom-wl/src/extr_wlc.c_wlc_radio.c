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
typedef  int wlc_param ;

/* Variables and functions */
 int GET ; 
 int PARAM_MODE ; 
 int /*<<< orphan*/  WLC_GET_RADIO ; 
 int /*<<< orphan*/  WLC_SET_RADIO ; 
 int /*<<< orphan*/  interface ; 
 int wl_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int wlc_radio(wlc_param param, void *data, void *value)
{
	int *val = (int *) value;
	int ret;

	if ((param & PARAM_MODE) == GET) {
		ret = wl_ioctl(interface, WLC_GET_RADIO, val, sizeof(int));
		*val = ((*val & 1) ? 0 : 1);
	} else {
		*val = (1 << 16) | (*val ? 0 : 1); 
		ret = wl_ioctl(interface, WLC_SET_RADIO, val, sizeof(int));
	}

	return ret;
}