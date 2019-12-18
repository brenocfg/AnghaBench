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
struct snd_soc_dai_link_component {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * name; } ;
struct snd_soc_component {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  client_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_graph_get_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int snd_soc_component_of_xlate_dai_id (struct snd_soc_component*,struct device_node*) ; 
 struct snd_soc_component* soc_find_component (struct snd_soc_dai_link_component*) ; 

int snd_soc_get_dai_id(struct device_node *ep)
{
	struct snd_soc_component *component;
	struct snd_soc_dai_link_component dlc;
	int ret;

	dlc.of_node	= of_graph_get_port_parent(ep);
	dlc.name	= NULL;
	/*
	 * For example HDMI case, HDMI has video/sound port,
	 * but ALSA SoC needs sound port number only.
	 * Thus counting HDMI DT port/endpoint doesn't work.
	 * Then, it should have .of_xlate_dai_id
	 */
	ret = -ENOTSUPP;
	mutex_lock(&client_mutex);
	component = soc_find_component(&dlc);
	if (component)
		ret = snd_soc_component_of_xlate_dai_id(component, ep);
	mutex_unlock(&client_mutex);

	of_node_put(dlc.of_node);

	return ret;
}