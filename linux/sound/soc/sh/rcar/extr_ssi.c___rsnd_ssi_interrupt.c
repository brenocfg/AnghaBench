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
struct rsnd_priv {int /*<<< orphan*/  lock; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int /*<<< orphan*/  substream; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DIRQ ; 
 int OIRQ ; 
 int UIRQ ; 
 int /*<<< orphan*/  rsnd_dai_period_elapsed (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_dbg_irq_status (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsnd_io_is_working (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_mod_name (struct rsnd_mod*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 int rsnd_ssi_is_dma_mode (struct rsnd_mod*) ; 
 int rsnd_ssi_pio_interrupt (struct rsnd_mod*,struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_ssi_status_clear (struct rsnd_mod*) ; 
 int rsnd_ssi_status_get (struct rsnd_mod*) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rsnd_ssi_interrupt(struct rsnd_mod *mod,
				 struct rsnd_dai_stream *io)
{
	struct rsnd_priv *priv = rsnd_mod_to_priv(mod);
	struct device *dev = rsnd_priv_to_dev(priv);
	int is_dma = rsnd_ssi_is_dma_mode(mod);
	u32 status;
	bool elapsed = false;
	bool stop = false;

	spin_lock(&priv->lock);

	/* ignore all cases if not working */
	if (!rsnd_io_is_working(io))
		goto rsnd_ssi_interrupt_out;

	status = rsnd_ssi_status_get(mod);

	/* PIO only */
	if (!is_dma && (status & DIRQ))
		elapsed = rsnd_ssi_pio_interrupt(mod, io);

	/* DMA only */
	if (is_dma && (status & (UIRQ | OIRQ))) {
		rsnd_dbg_irq_status(dev, "%s err status : 0x%08x\n",
			rsnd_mod_name(mod), status);

		stop = true;
	}

	rsnd_ssi_status_clear(mod);
rsnd_ssi_interrupt_out:
	spin_unlock(&priv->lock);

	if (elapsed)
		rsnd_dai_period_elapsed(io);

	if (stop)
		snd_pcm_stop_xrun(io->substream);

}