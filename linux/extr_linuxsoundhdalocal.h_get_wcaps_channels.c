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

/* Variables and functions */
 int AC_WCAP_CHAN_CNT_EXT ; 

__attribute__((used)) static inline unsigned int get_wcaps_channels(u32 wcaps)
{
	unsigned int chans;

	chans = (wcaps & AC_WCAP_CHAN_CNT_EXT) >> 13;
	chans = (chans + 1) * 2;

	return chans;
}