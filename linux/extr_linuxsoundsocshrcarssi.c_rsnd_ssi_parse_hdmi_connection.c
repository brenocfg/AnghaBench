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
struct rsnd_priv {int dummy; } ;
struct rsnd_dai {int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rsnd_ssi_parse_hdmi_connection (struct rsnd_priv*,int /*<<< orphan*/ *,struct device_node*) ; 
 struct device_node* of_graph_get_remote_endpoint (struct device_node*) ; 
 struct rsnd_dai* rsnd_rdai_get (struct rsnd_priv*,int) ; 

void rsnd_ssi_parse_hdmi_connection(struct rsnd_priv *priv,
				    struct device_node *endpoint,
				    int dai_i)
{
	struct rsnd_dai *rdai = rsnd_rdai_get(priv, dai_i);
	struct device_node *remote_ep;

	remote_ep = of_graph_get_remote_endpoint(endpoint);
	if (!remote_ep)
		return;

	__rsnd_ssi_parse_hdmi_connection(priv, &rdai->playback, remote_ep);
	__rsnd_ssi_parse_hdmi_connection(priv, &rdai->capture,  remote_ep);
}