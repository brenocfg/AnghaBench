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
struct rsnd_dai_stream {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rsnd_io_to_mod_ssi (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_parse_tdm_split_mode (struct rsnd_priv*,struct rsnd_dai_stream*,struct device_node*) ; 

__attribute__((used)) static void rsnd_parse_connect_simple(struct rsnd_priv *priv,
				      struct rsnd_dai_stream *io,
				      struct device_node *dai_np)
{
	if (!rsnd_io_to_mod_ssi(io))
		return;

	rsnd_parse_tdm_split_mode(priv, io, dai_np);
}