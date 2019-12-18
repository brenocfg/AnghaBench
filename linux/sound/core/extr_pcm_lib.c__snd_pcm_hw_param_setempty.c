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
 scalar_t__ hw_is_interval (int) ; 
 scalar_t__ hw_is_mask (int) ; 
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,int) ; 
 int /*<<< orphan*/  hw_param_mask (struct snd_pcm_hw_params*,int) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  snd_interval_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mask_none (int /*<<< orphan*/ ) ; 

void _snd_pcm_hw_param_setempty(struct snd_pcm_hw_params *params,
				snd_pcm_hw_param_t var)
{
	if (hw_is_mask(var)) {
		snd_mask_none(hw_param_mask(params, var));
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	} else if (hw_is_interval(var)) {
		snd_interval_none(hw_param_interval(params, var));
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	} else {
		snd_BUG();
	}
}