#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {int bg_channels; int a_channels; TYPE_2__* a; TYPE_1__* bg; } ;
struct libipw_device {int freq_band; int mode; TYPE_3__ geo; } ;
struct TYPE_5__ {scalar_t__ channel; int flags; } ;
struct TYPE_4__ {scalar_t__ channel; int flags; } ;

/* Variables and functions */
 int IEEE_G ; 
 int LIBIPW_24GHZ_BAND ; 
 int LIBIPW_52GHZ_BAND ; 
 int LIBIPW_CH_B_ONLY ; 
 int LIBIPW_CH_INVALID ; 

int libipw_is_valid_channel(struct libipw_device *ieee, u8 channel)
{
	int i;

	/* Driver needs to initialize the geography map before using
	 * these helper functions */
	if (ieee->geo.bg_channels == 0 && ieee->geo.a_channels == 0)
		return 0;

	if (ieee->freq_band & LIBIPW_24GHZ_BAND)
		for (i = 0; i < ieee->geo.bg_channels; i++)
			/* NOTE: If G mode is currently supported but
			 * this is a B only channel, we don't see it
			 * as valid. */
			if ((ieee->geo.bg[i].channel == channel) &&
			    !(ieee->geo.bg[i].flags & LIBIPW_CH_INVALID) &&
			    (!(ieee->mode & IEEE_G) ||
			     !(ieee->geo.bg[i].flags & LIBIPW_CH_B_ONLY)))
				return LIBIPW_24GHZ_BAND;

	if (ieee->freq_band & LIBIPW_52GHZ_BAND)
		for (i = 0; i < ieee->geo.a_channels; i++)
			if ((ieee->geo.a[i].channel == channel) &&
			    !(ieee->geo.a[i].flags & LIBIPW_CH_INVALID))
				return LIBIPW_52GHZ_BAND;

	return 0;
}