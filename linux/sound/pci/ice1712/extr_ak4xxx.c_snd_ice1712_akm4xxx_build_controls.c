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
struct snd_ice1712 {unsigned int akm_codecs; struct snd_akm4xxx* akm; } ;
struct snd_akm4xxx {int dummy; } ;

/* Variables and functions */
 int snd_akm4xxx_build_controls (struct snd_akm4xxx*) ; 

int snd_ice1712_akm4xxx_build_controls(struct snd_ice1712 *ice)
{
	unsigned int akidx;
	int err;

	for (akidx = 0; akidx < ice->akm_codecs; akidx++) {
		struct snd_akm4xxx *ak = &ice->akm[akidx];
		err = snd_akm4xxx_build_controls(ak);
		if (err < 0)
			return err;
	}
	return 0;
}