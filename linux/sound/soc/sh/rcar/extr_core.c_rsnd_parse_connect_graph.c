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
struct rsnd_dai_stream {int /*<<< orphan*/  name; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSND_STREAM_HDMI0 ; 
 int /*<<< orphan*/  RSND_STREAM_HDMI1 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  rsnd_flags_set (struct rsnd_dai_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_io_to_mod_ssi (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_parse_tdm_split_mode (struct rsnd_priv*,struct rsnd_dai_stream*,struct device_node*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void rsnd_parse_connect_graph(struct rsnd_priv *priv,
				     struct rsnd_dai_stream *io,
				     struct device_node *endpoint)
{
	struct device *dev = rsnd_priv_to_dev(priv);
	struct device_node *remote_node = of_graph_get_remote_port_parent(endpoint);

	if (!rsnd_io_to_mod_ssi(io))
		return;

	/* HDMI0 */
	if (strstr(remote_node->full_name, "hdmi@fead0000")) {
		rsnd_flags_set(io, RSND_STREAM_HDMI0);
		dev_dbg(dev, "%s connected to HDMI0\n", io->name);
	}

	/* HDMI1 */
	if (strstr(remote_node->full_name, "hdmi@feae0000")) {
		rsnd_flags_set(io, RSND_STREAM_HDMI1);
		dev_dbg(dev, "%s connected to HDMI1\n", io->name);
	}

	rsnd_parse_tdm_split_mode(priv, io, endpoint);
}