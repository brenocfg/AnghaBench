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
typedef  enum snd_ff_stream_mode { ____Placeholder_snd_ff_stream_mode } snd_ff_stream_mode ;
typedef  enum cip_sfc { ____Placeholder_cip_sfc } cip_sfc ;

/* Variables and functions */
#define  CIP_SFC_176400 137 
#define  CIP_SFC_192000 136 
#define  CIP_SFC_32000 135 
#define  CIP_SFC_44100 134 
#define  CIP_SFC_48000 133 
#define  CIP_SFC_88200 132 
#define  CIP_SFC_96000 131 
 int CIP_SFC_COUNT ; 
 int EINVAL ; 
#define  SND_FF_STREAM_MODE_HIGH 130 
#define  SND_FF_STREAM_MODE_LOW 129 
#define  SND_FF_STREAM_MODE_MID 128 

int snd_ff_stream_get_multiplier_mode(enum cip_sfc sfc,
				      enum snd_ff_stream_mode *mode)
{
	static const enum snd_ff_stream_mode modes[] = {
		[CIP_SFC_32000] = SND_FF_STREAM_MODE_LOW,
		[CIP_SFC_44100] = SND_FF_STREAM_MODE_LOW,
		[CIP_SFC_48000] = SND_FF_STREAM_MODE_LOW,
		[CIP_SFC_88200] = SND_FF_STREAM_MODE_MID,
		[CIP_SFC_96000] = SND_FF_STREAM_MODE_MID,
		[CIP_SFC_176400] = SND_FF_STREAM_MODE_HIGH,
		[CIP_SFC_192000] = SND_FF_STREAM_MODE_HIGH,
	};

	if (sfc >= CIP_SFC_COUNT)
		return -EINVAL;

	*mode = modes[sfc];

	return 0;
}