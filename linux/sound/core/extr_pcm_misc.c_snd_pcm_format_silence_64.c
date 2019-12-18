#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ snd_pcm_format_t ;
struct TYPE_2__ {unsigned char const* silence; int /*<<< orphan*/  phys; } ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_FORMAT_LAST ; 
 TYPE_1__* pcm_formats ; 

const unsigned char *snd_pcm_format_silence_64(snd_pcm_format_t format)
{
	if ((INT)format < 0 || (INT)format > (INT)SNDRV_PCM_FORMAT_LAST)
		return NULL;
	if (! pcm_formats[(INT)format].phys)
		return NULL;
	return pcm_formats[(INT)format].silence;
}