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
struct TYPE_2__ {int subdivision; int params; scalar_t__ fragshift; } ;
struct snd_pcm_runtime {TYPE_1__ oss; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int snd_pcm_oss_set_subdivide1(struct snd_pcm_substream *substream, int subdivide)
{
	struct snd_pcm_runtime *runtime;

	runtime = substream->runtime;
	if (subdivide == 0) {
		subdivide = runtime->oss.subdivision;
		if (subdivide == 0)
			subdivide = 1;
		return subdivide;
	}
	if (runtime->oss.subdivision || runtime->oss.fragshift)
		return -EINVAL;
	if (subdivide != 1 && subdivide != 2 && subdivide != 4 &&
	    subdivide != 8 && subdivide != 16)
		return -EINVAL;
	runtime->oss.subdivision = subdivide;
	runtime->oss.params = 1;
	return subdivide;
}