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
struct snd_pcm_runtime {int dummy; } ;
struct snd_pcm_hw_constraint_ratnums {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_hw_param_t ;

/* Variables and functions */
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_ratnums ; 

int snd_pcm_hw_constraint_ratnums(struct snd_pcm_runtime *runtime, 
				  unsigned int cond,
				  snd_pcm_hw_param_t var,
				  const struct snd_pcm_hw_constraint_ratnums *r)
{
	return snd_pcm_hw_rule_add(runtime, cond, var,
				   snd_pcm_hw_rule_ratnums, (void *)r,
				   var, -1);
}