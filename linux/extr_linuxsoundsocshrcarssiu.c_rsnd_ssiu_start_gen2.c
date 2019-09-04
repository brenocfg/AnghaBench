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
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSI_CONTROL ; 
 int /*<<< orphan*/  SSI_CTRL ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rsnd_ssi_multi_slaves_runtime (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_ssi_use_busif (struct rsnd_dai_stream*) ; 

__attribute__((used)) static int rsnd_ssiu_start_gen2(struct rsnd_mod *mod,
				struct rsnd_dai_stream *io,
				struct rsnd_priv *priv)
{
	if (!rsnd_ssi_use_busif(io))
		return 0;

	rsnd_mod_write(mod, SSI_CTRL, 0x1);

	if (rsnd_ssi_multi_slaves_runtime(io))
		rsnd_mod_write(mod, SSI_CONTROL, 0x1);

	return 0;
}