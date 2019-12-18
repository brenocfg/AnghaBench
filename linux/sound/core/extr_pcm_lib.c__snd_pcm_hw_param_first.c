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
struct snd_pcm_hw_params {int cmask; int rmask; } ;
typedef  int snd_pcm_hw_param_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ hw_is_interval (int) ; 
 scalar_t__ hw_is_mask (int) ; 
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,int) ; 
 int /*<<< orphan*/  hw_param_mask (struct snd_pcm_hw_params*,int) ; 
 int snd_interval_refine_first (int /*<<< orphan*/ ) ; 
 int snd_mask_refine_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _snd_pcm_hw_param_first(struct snd_pcm_hw_params *params,
				   snd_pcm_hw_param_t var)
{
	int changed;
	if (hw_is_mask(var))
		changed = snd_mask_refine_first(hw_param_mask(params, var));
	else if (hw_is_interval(var))
		changed = snd_interval_refine_first(hw_param_interval(params, var));
	else
		return -EINVAL;
	if (changed > 0) {
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	}
	return changed;
}