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
struct snd_pcm_substream {int /*<<< orphan*/  buffer_bytes_max; } ;
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; struct snd_pcm_substream* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {int integer; scalar_t__ openmax; scalar_t__ openmin; int /*<<< orphan*/  max; scalar_t__ min; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_refine (int /*<<< orphan*/ ,struct snd_interval*) ; 

__attribute__((used)) static int snd_pcm_hw_rule_buffer_bytes_max(struct snd_pcm_hw_params *params,
					    struct snd_pcm_hw_rule *rule)
{
	struct snd_interval t;
	struct snd_pcm_substream *substream = rule->private;
	t.min = 0;
	t.max = substream->buffer_bytes_max;
	t.openmin = 0;
	t.openmax = 0;
	t.integer = 1;
	return snd_interval_refine(hw_param_interval(params, rule->var), &t);
}