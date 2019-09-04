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
 int AC_SUPPCM_BITS_8 ; 
 int ARRAY_SIZE (unsigned int*) ; 
 scalar_t__ snprintf (char*,int,char*,unsigned int) ; 

void snd_print_pcm_bits(int pcm, char *buf, int buflen)
{
	static unsigned int bits[] = { 8, 16, 20, 24, 32 };
	int i, j;

	for (i = 0, j = 0; i < ARRAY_SIZE(bits); i++)
		if (pcm & (AC_SUPPCM_BITS_8 << i))
			j += snprintf(buf + j, buflen - j,  " %d", bits[i]);

	buf[j] = '\0'; /* necessary when j == 0 */
}