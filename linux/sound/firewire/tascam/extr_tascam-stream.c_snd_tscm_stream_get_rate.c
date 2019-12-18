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

/* Variables and functions */
 int EAGAIN ; 
 int get_clock (struct snd_tscm*,int*) ; 

int snd_tscm_stream_get_rate(struct snd_tscm *tscm, unsigned int *rate)
{
	u32 data;
	int err;

	err = get_clock(tscm, &data);
	if (err < 0)
		return err;

	data = (data & 0xff000000) >> 24;

	/* Check base rate. */
	if ((data & 0x0f) == 0x01)
		*rate = 44100;
	else if ((data & 0x0f) == 0x02)
		*rate = 48000;
	else
		return -EAGAIN;

	/* Check multiplier. */
	if ((data & 0xf0) == 0x80)
		*rate *= 2;
	else if ((data & 0xf0) != 0x00)
		return -EAGAIN;

	return err;
}