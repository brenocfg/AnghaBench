#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hdspm {TYPE_2__* mixer; } ;
struct TYPE_4__ {TYPE_1__* ch; } ;
struct TYPE_3__ {unsigned short* in; } ;

/* Variables and functions */
 scalar_t__ HDSPM_MADI_mixerBase ; 
 unsigned int HDSPM_MIXER_CHANNELS ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,scalar_t__,unsigned short) ; 

__attribute__((used)) static int hdspm_write_in_gain(struct hdspm *hdspm, unsigned int chan,
				      unsigned int in, unsigned short data)
{
	if (chan >= HDSPM_MIXER_CHANNELS || in >= HDSPM_MIXER_CHANNELS)
		return -1;

	hdspm_write(hdspm,
		    HDSPM_MADI_mixerBase +
		    ((in + 128 * chan) * sizeof(u32)),
		    (hdspm->mixer->ch[chan].in[in] = data & 0xFFFF));
	return 0;
}