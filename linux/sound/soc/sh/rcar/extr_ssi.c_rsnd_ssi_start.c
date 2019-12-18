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
struct rsnd_ssi {int cr_en; int cr_own; int cr_clk; int cr_mode; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int EN ; 
 int /*<<< orphan*/  SSICR ; 
 struct rsnd_ssi* rsnd_mod_to_ssi (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rsnd_ssi_is_parent (struct rsnd_mod*,struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_ssi_is_run_mods (struct rsnd_mod*,struct rsnd_dai_stream*) ; 
 scalar_t__ rsnd_ssi_multi_slaves_runtime (struct rsnd_dai_stream*) ; 

__attribute__((used)) static int rsnd_ssi_start(struct rsnd_mod *mod,
			  struct rsnd_dai_stream *io,
			  struct rsnd_priv *priv)
{
	struct rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);

	if (!rsnd_ssi_is_run_mods(mod, io))
		return 0;

	/*
	 * EN will be set via SSIU :: SSI_CONTROL
	 * if Multi channel mode
	 */
	if (rsnd_ssi_multi_slaves_runtime(io))
		return 0;

	/*
	 * EN is for data output.
	 * SSI parent EN is not needed.
	 */
	if (rsnd_ssi_is_parent(mod, io))
		return 0;

	ssi->cr_en = EN;

	rsnd_mod_write(mod, SSICR,	ssi->cr_own	|
					ssi->cr_clk	|
					ssi->cr_mode	|
					ssi->cr_en);

	return 0;
}