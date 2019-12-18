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
struct snd_soc_pcm_runtime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  headset_jack ; 
 int /*<<< orphan*/  rk_jack_nb ; 
 int /*<<< orphan*/  snd_soc_jack_notifier_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rk_init(struct snd_soc_pcm_runtime *runtime)
{
	/*
	 * The jack has already been created in the rk_98090_headset_init()
	 * function.
	 */
	snd_soc_jack_notifier_register(&headset_jack, &rk_jack_nb);

	return 0;
}