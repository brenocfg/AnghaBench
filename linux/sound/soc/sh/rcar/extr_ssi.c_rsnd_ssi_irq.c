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
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSI_INT_ENABLE ; 
 scalar_t__ rsnd_is_gen1 (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rsnd_ssi_is_dma_mode (struct rsnd_mod*) ; 
 scalar_t__ rsnd_ssi_is_parent (struct rsnd_mod*,struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_ssi_is_run_mods (struct rsnd_mod*,struct rsnd_dai_stream*) ; 

__attribute__((used)) static int rsnd_ssi_irq(struct rsnd_mod *mod,
			struct rsnd_dai_stream *io,
			struct rsnd_priv *priv,
			int enable)
{
	u32 val = 0;

	if (rsnd_is_gen1(priv))
		return 0;

	if (rsnd_ssi_is_parent(mod, io))
		return 0;

	if (!rsnd_ssi_is_run_mods(mod, io))
		return 0;

	if (enable)
		val = rsnd_ssi_is_dma_mode(mod) ? 0x0e000000 : 0x0f000000;

	rsnd_mod_write(mod, SSI_INT_ENABLE, val);

	return 0;
}