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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  RSND_SSI_PROBED ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_flags_has (struct rsnd_ssi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_flags_set (struct rsnd_ssi*,int /*<<< orphan*/ ) ; 
 struct rsnd_ssi* rsnd_mod_to_ssi (struct rsnd_mod*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_ssi_interrupt ; 
 scalar_t__ rsnd_ssi_is_multi_slave (struct rsnd_mod*,struct rsnd_dai_stream*) ; 

__attribute__((used)) static int rsnd_ssi_common_probe(struct rsnd_mod *mod,
				 struct rsnd_dai_stream *io,
				 struct rsnd_priv *priv)
{
	struct device *dev = rsnd_priv_to_dev(priv);
	struct rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	int ret = 0;

	/*
	 * SSIP/SSIU/IRQ are not needed on
	 * SSI Multi slaves
	 */
	if (rsnd_ssi_is_multi_slave(mod, io))
		return 0;

	/*
	 * It can't judge ssi parent at this point
	 * see rsnd_ssi_pcm_new()
	 */

	/*
	 * SSI might be called again as PIO fallback
	 * It is easy to manual handling for IRQ request/free
	 *
	 * OTOH, this function might be called many times if platform is
	 * using MIX. It needs xxx_attach() many times on xxx_probe().
	 * Because of it, we can't control .probe/.remove calling count by
	 * mod->status.
	 * But it don't need to call request_irq() many times.
	 * Let's control it by RSND_SSI_PROBED flag.
	 */
	if (!rsnd_flags_has(ssi, RSND_SSI_PROBED)) {
		ret = request_irq(ssi->irq,
				  rsnd_ssi_interrupt,
				  IRQF_SHARED,
				  dev_name(dev), mod);

		rsnd_flags_set(ssi, RSND_SSI_PROBED);
	}

	return ret;
}