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
struct rsnd_ssi {int cr_own; int cr_clk; scalar_t__ cr_en; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRQ ; 
 int EN ; 
 int /*<<< orphan*/  IIRQ ; 
 int /*<<< orphan*/  SSICR ; 
 scalar_t__ rsnd_io_is_play (struct rsnd_dai_stream*) ; 
 struct rsnd_ssi* rsnd_mod_to_ssi (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rsnd_ssi_is_parent (struct rsnd_mod*,struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_ssi_is_run_mods (struct rsnd_mod*,struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_ssi_status_check (struct rsnd_mod*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsnd_ssi_stop(struct rsnd_mod *mod,
			 struct rsnd_dai_stream *io,
			 struct rsnd_priv *priv)
{
	struct rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	u32 cr;

	if (!rsnd_ssi_is_run_mods(mod, io))
		return 0;

	if (rsnd_ssi_is_parent(mod, io))
		return 0;

	cr  =	ssi->cr_own	|
		ssi->cr_clk;

	/*
	 * disable all IRQ,
	 * Playback: Wait all data was sent
	 * Capture:  It might not receave data. Do nothing
	 */
	if (rsnd_io_is_play(io)) {
		rsnd_mod_write(mod, SSICR, cr | EN);
		rsnd_ssi_status_check(mod, DIRQ);
	}

	/*
	 * disable SSI,
	 * and, wait idle state
	 */
	rsnd_mod_write(mod, SSICR, cr);	/* disabled all */
	rsnd_ssi_status_check(mod, IIRQ);

	ssi->cr_en = 0;

	return 0;
}