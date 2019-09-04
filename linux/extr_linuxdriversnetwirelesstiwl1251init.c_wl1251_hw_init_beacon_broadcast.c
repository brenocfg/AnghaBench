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
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int wl1251_acx_bcn_dtim_options (struct wl1251*) ; 

int wl1251_hw_init_beacon_broadcast(struct wl1251 *wl)
{
	int ret;

	ret = wl1251_acx_bcn_dtim_options(wl);
	if (ret < 0)
		return ret;

	return 0;
}