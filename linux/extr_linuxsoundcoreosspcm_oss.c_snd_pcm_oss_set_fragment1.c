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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {unsigned int fragshift; unsigned int maxfrags; int params; scalar_t__ subdivision; } ;
struct snd_pcm_runtime {TYPE_1__ oss; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int snd_pcm_oss_set_fragment1(struct snd_pcm_substream *substream, unsigned int val)
{
	struct snd_pcm_runtime *runtime;

	runtime = substream->runtime;
	if (runtime->oss.subdivision || runtime->oss.fragshift)
		return -EINVAL;
	runtime->oss.fragshift = val & 0xffff;
	runtime->oss.maxfrags = (val >> 16) & 0xffff;
	if (runtime->oss.fragshift < 4)		/* < 16 */
		runtime->oss.fragshift = 4;
	if (runtime->oss.maxfrags < 2)
		runtime->oss.maxfrags = 2;
	runtime->oss.params = 1;
	return 0;
}