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
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; int /*<<< orphan*/ * deps; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_param_interval_c (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_interval_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_interval*) ; 
 int snd_interval_refine (int /*<<< orphan*/ ,struct snd_interval*) ; 

__attribute__((used)) static int snd_pcm_hw_rule_mul(struct snd_pcm_hw_params *params,
			       struct snd_pcm_hw_rule *rule)
{
	struct snd_interval t;
	snd_interval_mul(hw_param_interval_c(params, rule->deps[0]),
		     hw_param_interval_c(params, rule->deps[1]), &t);
	return snd_interval_refine(hw_param_interval(params, rule->var), &t);
}