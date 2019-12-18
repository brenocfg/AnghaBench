#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ snd_pcm_format_t ;
struct TYPE_3__ {scalar_t__ alsa; int sndif; } ;

/* Variables and functions */
 TYPE_1__* ALSA_SNDIF_FORMATS ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 

__attribute__((used)) static int to_sndif_format(snd_pcm_format_t format)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ALSA_SNDIF_FORMATS); i++)
		if (ALSA_SNDIF_FORMATS[i].alsa == format)
			return ALSA_SNDIF_FORMATS[i].sndif;

	return -EINVAL;
}