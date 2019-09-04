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
struct TYPE_2__ {int phys; } ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_FORMAT_LAST ; 
 TYPE_1__* pcm_formats ; 

int snd_pcm_format_physical_width(snd_pcm_format_t format)
{
	int val;
	if ((INT)format < 0 || (INT)format > (INT)SNDRV_PCM_FORMAT_LAST)
		return -EINVAL;
	if ((val = pcm_formats[(INT)format].phys) == 0)
		return -EINVAL;
	return val;
}