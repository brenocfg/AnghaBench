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
struct snd_sof_dev {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* pcm_pointer ) (struct snd_sof_dev*,struct snd_pcm_substream*) ;} ;

/* Variables and functions */
 TYPE_1__* sof_ops (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  stub1 (struct snd_sof_dev*,struct snd_pcm_substream*) ; 

__attribute__((used)) static inline snd_pcm_uframes_t
snd_sof_pcm_platform_pointer(struct snd_sof_dev *sdev,
			     struct snd_pcm_substream *substream)
{
	if (sof_ops(sdev) && sof_ops(sdev)->pcm_pointer)
		return sof_ops(sdev)->pcm_pointer(sdev, substream);

	return 0;
}