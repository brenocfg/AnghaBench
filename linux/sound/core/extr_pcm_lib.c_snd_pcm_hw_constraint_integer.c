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
typedef  int /*<<< orphan*/  snd_pcm_hw_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  constrs_interval (struct snd_pcm_hw_constraints*,int /*<<< orphan*/ ) ; 
 int snd_interval_setinteger (int /*<<< orphan*/ ) ; 

int snd_pcm_hw_constraint_integer(struct snd_pcm_runtime *runtime, snd_pcm_hw_param_t var)
{
	struct snd_pcm_hw_constraints *constrs = &runtime->hw_constraints;
	return snd_interval_setinteger(constrs_interval(constrs, var));
}