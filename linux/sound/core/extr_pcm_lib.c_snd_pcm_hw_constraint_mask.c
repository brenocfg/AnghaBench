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
typedef  int /*<<< orphan*/  u_int32_t ;
struct snd_pcm_hw_constraints {int dummy; } ;
struct snd_pcm_runtime {struct snd_pcm_hw_constraints hw_constraints; } ;
struct snd_mask {int /*<<< orphan*/ * bits; } ;
typedef  int /*<<< orphan*/  snd_pcm_hw_param_t ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_MASK_MAX ; 
 struct snd_mask* constrs_mask (struct snd_pcm_hw_constraints*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int snd_pcm_hw_constraint_mask(struct snd_pcm_runtime *runtime, snd_pcm_hw_param_t var,
			       u_int32_t mask)
{
	struct snd_pcm_hw_constraints *constrs = &runtime->hw_constraints;
	struct snd_mask *maskp = constrs_mask(constrs, var);
	*maskp->bits &= mask;
	memset(maskp->bits + 1, 0, (SNDRV_MASK_MAX-32) / 8); /* clear rest */
	if (*maskp->bits == 0)
		return -EINVAL;
	return 0;
}