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
struct snd_pcm_hw_constraints {int dummy; } ;
struct snd_pcm_runtime {struct snd_pcm_hw_constraints hw_constraints; } ;
struct snd_interval {unsigned int min; unsigned int max; scalar_t__ integer; scalar_t__ openmax; scalar_t__ openmin; } ;
typedef  int /*<<< orphan*/  snd_pcm_hw_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  constrs_interval (struct snd_pcm_hw_constraints*,int /*<<< orphan*/ ) ; 
 int snd_interval_refine (int /*<<< orphan*/ ,struct snd_interval*) ; 

int snd_pcm_hw_constraint_minmax(struct snd_pcm_runtime *runtime, snd_pcm_hw_param_t var,
				 unsigned int min, unsigned int max)
{
	struct snd_pcm_hw_constraints *constrs = &runtime->hw_constraints;
	struct snd_interval t;
	t.min = min;
	t.max = max;
	t.openmin = t.openmax = 0;
	t.integer = 0;
	return snd_interval_refine(constrs_interval(constrs, var), &t);
}