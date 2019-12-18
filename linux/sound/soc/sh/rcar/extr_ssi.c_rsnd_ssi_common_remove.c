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
struct rsnd_ssi {int /*<<< orphan*/  irq; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSND_SSI_PROBED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_flags_del (struct rsnd_ssi*,int /*<<< orphan*/ ) ; 
 scalar_t__ rsnd_flags_has (struct rsnd_ssi*,int /*<<< orphan*/ ) ; 
 struct rsnd_mod* rsnd_io_to_mod_ssi (struct rsnd_dai_stream*) ; 
 struct rsnd_ssi* rsnd_mod_to_ssi (struct rsnd_mod*) ; 

__attribute__((used)) static int rsnd_ssi_common_remove(struct rsnd_mod *mod,
				  struct rsnd_dai_stream *io,
				  struct rsnd_priv *priv)
{
	struct rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	struct rsnd_mod *pure_ssi_mod = rsnd_io_to_mod_ssi(io);

	/* Do nothing if non SSI (= SSI parent, multi SSI) mod */
	if (pure_ssi_mod != mod)
		return 0;

	/* PIO will request IRQ again */
	if (rsnd_flags_has(ssi, RSND_SSI_PROBED)) {
		free_irq(ssi->irq, mod);

		rsnd_flags_del(ssi, RSND_SSI_PROBED);
	}

	return 0;
}