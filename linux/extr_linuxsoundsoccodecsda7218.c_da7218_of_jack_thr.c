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
typedef  int u32 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum da7218_hpldet_jack_thr { ____Placeholder_da7218_hpldet_jack_thr } da7218_hpldet_jack_thr ;

/* Variables and functions */
 int DA7218_HPLDET_JACK_THR_84PCT ; 
 int DA7218_HPLDET_JACK_THR_88PCT ; 
 int DA7218_HPLDET_JACK_THR_92PCT ; 
 int DA7218_HPLDET_JACK_THR_96PCT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum da7218_hpldet_jack_thr
	da7218_of_jack_thr(struct snd_soc_component *component, u32 val)
{
	switch (val) {
	case 84:
		return DA7218_HPLDET_JACK_THR_84PCT;
	case 88:
		return DA7218_HPLDET_JACK_THR_88PCT;
	case 92:
		return DA7218_HPLDET_JACK_THR_92PCT;
	case 96:
		return DA7218_HPLDET_JACK_THR_96PCT;
	default:
		dev_warn(component->dev, "Invalid jack threshold level");
		return DA7218_HPLDET_JACK_THR_84PCT;
	}
}