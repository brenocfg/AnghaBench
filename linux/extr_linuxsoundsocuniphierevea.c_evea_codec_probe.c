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
struct snd_soc_component {int dummy; } ;
struct evea_priv {int switch_lin; int switch_lo; int switch_hp; } ;

/* Variables and functions */
 int /*<<< orphan*/  evea_set_power_state_on (struct evea_priv*) ; 
 int /*<<< orphan*/  evea_update_switch_all (struct evea_priv*) ; 
 struct evea_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int evea_codec_probe(struct snd_soc_component *component)
{
	struct evea_priv *evea = snd_soc_component_get_drvdata(component);

	evea->switch_lin = 1;
	evea->switch_lo = 1;
	evea->switch_hp = 1;

	evea_set_power_state_on(evea);
	evea_update_switch_all(evea);

	return 0;
}