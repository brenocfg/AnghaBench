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
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {int dummy; } ;
struct snd_interval {int openmin; } ;
typedef  int /*<<< orphan*/  snd_pcm_hw_param_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ hw_is_interval (int /*<<< orphan*/ ) ; 
 scalar_t__ hw_is_mask (int /*<<< orphan*/ ) ; 
 struct snd_interval* hw_param_interval_c (struct snd_pcm_hw_params const*,int /*<<< orphan*/ ) ; 
 struct snd_mask* hw_param_mask_c (struct snd_pcm_hw_params const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_interval_single (struct snd_interval const*) ; 
 int snd_interval_value (struct snd_interval const*) ; 
 int /*<<< orphan*/  snd_mask_single (struct snd_mask const*) ; 
 int snd_mask_value (struct snd_mask const*) ; 

int snd_pcm_hw_param_value(const struct snd_pcm_hw_params *params,
			   snd_pcm_hw_param_t var, int *dir)
{
	if (hw_is_mask(var)) {
		const struct snd_mask *mask = hw_param_mask_c(params, var);
		if (!snd_mask_single(mask))
			return -EINVAL;
		if (dir)
			*dir = 0;
		return snd_mask_value(mask);
	}
	if (hw_is_interval(var)) {
		const struct snd_interval *i = hw_param_interval_c(params, var);
		if (!snd_interval_single(i))
			return -EINVAL;
		if (dir)
			*dir = i->openmin;
		return snd_interval_value(i);
	}
	return -EINVAL;
}