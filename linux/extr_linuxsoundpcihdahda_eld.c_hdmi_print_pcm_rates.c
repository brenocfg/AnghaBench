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

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 scalar_t__ snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static void hdmi_print_pcm_rates(int pcm, char *buf, int buflen)
{
	static unsigned int alsa_rates[] = {
		5512, 8000, 11025, 16000, 22050, 32000, 44100, 48000, 64000,
		88200, 96000, 176400, 192000, 384000
	};
	int i, j;

	for (i = 0, j = 0; i < ARRAY_SIZE(alsa_rates); i++)
		if (pcm & (1 << i))
			j += snprintf(buf + j, buflen - j,  " %d",
				alsa_rates[i]);

	buf[j] = '\0'; /* necessary when j == 0 */
}