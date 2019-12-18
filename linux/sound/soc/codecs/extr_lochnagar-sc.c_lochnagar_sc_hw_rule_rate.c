#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; int /*<<< orphan*/ * deps; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {int min; int max; } ;
struct TYPE_3__ {int max; } ;

/* Variables and functions */
 TYPE_1__* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_refine (TYPE_1__*,struct snd_interval*) ; 

__attribute__((used)) static int lochnagar_sc_hw_rule_rate(struct snd_pcm_hw_params *params,
				     struct snd_pcm_hw_rule *rule)
{
	struct snd_interval range = {
		.min = 8000,
		.max = 24576000 / hw_param_interval(params, rule->deps[0])->max,
	};

	return snd_interval_refine(hw_param_interval(params, rule->var),
				   &range);
}