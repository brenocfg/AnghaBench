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
struct snd_tscm {int dummy; } ;
typedef  enum snd_tscm_clock { ____Placeholder_snd_tscm_clock } snd_tscm_clock ;

/* Variables and functions */
 int EIO ; 
 int SND_TSCM_CLOCK_ADAT ; 
 int get_clock (struct snd_tscm*,int*) ; 

int snd_tscm_stream_get_clock(struct snd_tscm *tscm, enum snd_tscm_clock *clock)
{
	u32 data;
	int err;

	err = get_clock(tscm, &data);
	if (err < 0)
		return err;

	*clock = ((data & 0x00ff0000) >> 16) - 1;
	if (*clock < 0 || *clock > SND_TSCM_CLOCK_ADAT)
		return -EIO;

	return 0;
}