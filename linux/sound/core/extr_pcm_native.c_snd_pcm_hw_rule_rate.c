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
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; struct snd_pcm_hardware* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_pcm_hardware {int /*<<< orphan*/  rates; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ snd_pcm_known_rates ; 

__attribute__((used)) static int snd_pcm_hw_rule_rate(struct snd_pcm_hw_params *params,
				struct snd_pcm_hw_rule *rule)
{
	struct snd_pcm_hardware *hw = rule->private;
	return snd_interval_list(hw_param_interval(params, rule->var),
				 snd_pcm_known_rates.count,
				 snd_pcm_known_rates.list, hw->rates);
}