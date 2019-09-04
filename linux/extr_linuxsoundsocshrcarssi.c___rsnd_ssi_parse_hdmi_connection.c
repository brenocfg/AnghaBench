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
struct rsnd_ssi {int dummy; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSND_SSI_HDMI0 ; 
 int /*<<< orphan*/  RSND_SSI_HDMI1 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  rsnd_flags_set (struct rsnd_ssi*,int /*<<< orphan*/ ) ; 
 struct rsnd_mod* rsnd_io_to_mod_ssi (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_is_gen3 (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_mod_id (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_name (struct rsnd_mod*) ; 
 struct rsnd_ssi* rsnd_mod_to_ssi (struct rsnd_mod*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void __rsnd_ssi_parse_hdmi_connection(struct rsnd_priv *priv,
					     struct rsnd_dai_stream *io,
					     struct device_node *remote_ep)
{
	struct device *dev = rsnd_priv_to_dev(priv);
	struct rsnd_mod *mod = rsnd_io_to_mod_ssi(io);
	struct rsnd_ssi *ssi;
	struct device_node *remote_node = of_graph_get_port_parent(remote_ep);

	/* support Gen3 only */
	if (!rsnd_is_gen3(priv))
		return;

	if (!mod)
		return;

	ssi  = rsnd_mod_to_ssi(mod);

	/* HDMI0 */
	if (strstr(remote_node->full_name, "hdmi@fead0000")) {
		rsnd_flags_set(ssi, RSND_SSI_HDMI0);
		dev_dbg(dev, "%s[%d] connected to HDMI0\n",
			 rsnd_mod_name(mod), rsnd_mod_id(mod));
	}

	/* HDMI1 */
	if (strstr(remote_node->full_name, "hdmi@feae0000")) {
		rsnd_flags_set(ssi, RSND_SSI_HDMI1);
		dev_dbg(dev, "%s[%d] connected to HDMI1\n",
			rsnd_mod_name(mod), rsnd_mod_id(mod));
	}
}